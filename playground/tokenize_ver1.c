#include "../execute.h"

char *save_text_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr && !is_delim(*ptr))
		ptr++;
	return (--ptr);
}

char *save_space_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr && is_ifs(*ptr))
		ptr++;
	return (--ptr);
}

char *save_redir_last(char *begining)
{
	char *ptr;
	
	ptr = begining + sizeof(char);
	if (*begining == *ptr)
		return (ptr);
	else
		return (begining);
}

char *save_quote_last(char *begining)			//クォート内を抜き出す
{
	char *ptr;

	ptr = begining + sizeof(char);
	while(*ptr != '\0' && *ptr != *begining)
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	return (ptr);
}

char *save_env_last(char *begining)
{
	char *ptr;

	ptr = begining + sizeof(char);
	if (*ptr == '?' || *ptr == '$') 			//そのまま
		return (ptr);
	if (is_quote(*ptr))							//クォート内を抜き出す
		return (save_quote_last(ptr));
	if (*ptr == '\0' || is_delim(*ptr))			//そのまま
		return (begining);
	return (save_text_last(ptr));				//そのまま
}


char *save_last_chr(char *begining)
{
	if (*begining == '$')
		return (save_env_last(begining));
	else if (*begining == '\"' || *begining == '\'')
		return (save_quote_last(begining));
	else if (*begining == '>' || *begining == '<')
		return (save_redir_last(begining));
	else if (*begining == '|')
		return (begining);
	else if(is_ifs(*begining))
		return (save_space_last(begining));
	else
		return (save_text_last(begining));
}

char *tkn_substr(char *begining, char *last)
{
	size_t len;

	len = (size_t)((last - begining)/sizeof(char) + sizeof(char));
	return (ft_xsubstr(begining, 0, len));
}

//lenはクォーテーション内の文字数+1文字分
char *tkn_substr_into_quote(char *begining, char *last)
{
	size_t len;

	while(*begining != *last)
		begining++;
	len = (size_t)((--last - ++begining)/sizeof(char) + sizeof(char));
	return (ft_xsubstr(begining, 0, len));
}

// is_quote(*last)で判断したいのは、クォートトークンか{$""/$''}の形かどうか
t_token *tkn_make_new(char *begining, char *last)
{
	t_token *node = (t_token *)malloc(sizeof(t_token));
	if(is_quote(*last))
		node->val = tkn_substr_into_quote(begining, last);
	else
		node->val = tkn_substr(begining, last);
	node->kind = tkn_save_kind(begining);
	node->next = NULL;
	return (node);
}

t_token *tokenize(char *line_ptr)
{
	char		*last;
	t_token 	*head;
	t_token 	*new;

	head = NULL;
	while(*line_ptr)
	{
		last = save_last_chr(line_ptr);
		// print_to_last(line_ptr, last);
		if (last == NULL)
		{
			tkn_free_list(head);
			return (NULL);
		}
		new = tkn_make_new(line_ptr, last);
		tkn_add_last(&head, new);
		line_ptr = ++last;
	}
	return (head);
}