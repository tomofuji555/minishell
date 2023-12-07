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
