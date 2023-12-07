
enum e_token_type
{
	TKN_SPACE,
	TKN_TEXT,
	TKN_S_QUOTE,
	TKN_D_QUOTE,
	TKN_ENV,
	TKN_PIPE,
	TKN_IN_FILE,
	TKN_HERE_DOC,
	TKN_OUT_FILE,
	TKN_APPEND_FILE,
};

// enum e_chunk_type
// {
// 	CHK_TEXT, //text,s_quote,d_quote,env
// 	CHK_PIPE, // | 
// 	CHK_IN_FILE, // < + text,s_quote,d_quote,env
// 	CHK_HERE_DOC, // << + text,s_quote,d_quote,env
// 	CHK_OUT_FILE, // > + text,s_quote,d_quote,env
// 	CHK_APPEND_FILE, // >> + text,s_quote,d_quote,env
// };

typedef struct s_token
{
	enum e_token_type	token_type;
	char				*val;
	struct s_token		*next;
}	t_token;

typedef struct s_node
{
	t_token			*cmd_tokens;
	t_token			*infile_tokens;
	t_token			*outfile_tokens;
	struct s_node	*prev;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_tree_node
{
	char	**strs;
	char	*infile_path;
	char 	*outfile_path;
}	t_tree_node;



----------トークンの条件----------
<スペーストークン>
	同じスペースなら回し続ける
<クォートトークン>
	同じ値のクォートが見つかるまで回す
		ex)"abc" => d_quoteのval.(abc)
			'kkk' => s_quoteのval.(kkk)
<テキストトークン>
	今回の指定文字(スペース、リダイレクト、パイプ、ドル、クォート)が来るまで回す
<ENVトークンかTEXTトークン>
	$が来たとき、次の値が...
	・テキスト(一文字目が'?'の場合)
		?ですぐに切り上げ、val=? ->TKN_ENVに
	・テキスト
		val=次の区切り文字手前まで -> TKN_ENVに
	・クォート
		val=クォート内 -> TKN_TEXTに
	・クォート以外の指定文字
		val=＄ -> TKN_TEXTに
<リダイレクトトークン>
	次の値を見て、同じリダイレクト文字だったらそれをまとめてトークンにする
		ex)>>、<<
	ただし、2個まで
		ex)>>>> == >>,>>
<パイプトークン>
	パイプのみトークンにする



----------環境変数の区切り----------
パイプ
リダイレクト
スペース(最初もKO)
ドル
クォート



----------リダイレクトの区切り----------
スペース(最初のはOK)
パイプ
リダイレクト


----------in/outfile_tokensに入れるには----------
1.リダイレクト系トークンを見つける
2.スペーストークンがあったら消す
3.直後のトークンが(パイプ || リダイレクト)なら、エラー
4.(テキスト || env || クォート)トークンであれば回し続け、それ以外が来れば終了する

それ以外のトークンはstring_tokensに入れる



// ----------チャンクの条件----------
// スペーストークン => 飛ばす
// パイプトークン => そのままパイプチャンクに
// <リダイレクトチャンク>
// 	リダイレクトトークンを見つけたら...
// 	1.スペーストークンを飛ばす
// 	2.トークンのタイプが(テキスト || env || クォート)であれば回し続け、リダイレクトチャンクにする
// 	※スペースが来たら、そこで終了
// 	※リダイレクトトークンの次のトークンが(パイプ || リダイレクト)なら、エラー
// <テキストチャンク>
// 	(テキスト || クォート || env)トークンを見つけたら...
// 	次のトークンが(テキスト || クォート || env)なら回し続け、テキストチャンクにする
// 	※スペースが来たら、そこで終了


// チャンクの方針{
// ・<テキストチャンク> …(テキスト)、(クォート)、(ドル)の集まり
// 	(テキスト) or (クォート) or (ドル)なら<テキストチャンク>でくっつける
// 	もちろん、<テキストチャンク>の中に(スペース)は入れてはいけない

// ・<envチャンク>
// 	(ドル)<テキストトークン>の繋がりなら、<envチャンク>で囲う
// 	そうじゃなければ<テキストチャンク>として判断
// 	(ドル)(スペース)<テキストトークン>でもバツ
// 	ex) $->(aaa) => envチャンクのval=(aaa)
// 		$-> ->(aaa) => テキストチャンクのval=($)

// ・<リダイレクトチャンク>
// 	(スペース)があれば飛ばす
// 	その後に、<テキストチャンク>系があれば、それらを<リダイレクトチャンク>で囲う
// 	(リダイレクト)の次が(パイプ) or (リダイレクト)ならエラー

// ・<パイプチャンク>
// 	(パイプ)を<パイプチャンク>にそのままする。
// }

