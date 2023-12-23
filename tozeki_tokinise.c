#include "execute.h"

char *get_text_last(char *begining)
{
	char *ptr = begining;
	while(*ptr != '\0' && is_text(*ptr))
		ptr++;
	return (ptr);
}

char *get_redir_last(char *begining)
{
	char *ptr = begining;
	if (*begining == *(++ptr))
		return (ptr);
	return (begining);
}

char *get_dq_last(char *begining)
{
	char *ptr = begining;
	while(*ptr != '\0' && !is_dq(*ptr))
		ptr++;
	return (ptr);
}

char *get_env_last(char *begining)
{
	char *ptr = ++begining;
	if (*ptr == '?' || *ptr == '$')
		return (ptr);
	while(*ptr != '\0' && is_space(*ptr))
		ptr++;
	if (is_dq(*ptr))
		return (get_dq_last(ptr));
	if (is_text(*ptr))
		retun (get_text_last(ptr));
	return (begining);
}

get_last(char *begining) //dq=ダブルクォート
{
	if(is_text(*begining))
		return (get_text_last(begining));
	else if (is_redir(*begining))
		return (get_redir_last(begining));
	else if (is_dq(*begining))
		return (get_dq_last(begining));
	else if (is_env(*begining))
		return (get_env_last(begining));
}

enum e_token_kind get_kind(char *begining, char *last)
{
	if (is_env(*begining))
	{
		if (*begining == *last || is_dq(++begining))
			return (TKN_TEXT);
		else
			return (TKN_ENV);
	}
	else if(is_redir(*begining))
		retun (TKN_IN_FILE); //本当はif文必須
	else if (is_dq(*begining))
		return (TKN_D_QUOTE);
	else if (is_text(*begining))
		return (TKN_TEXT);
	else
		return (-1);
}

t_token *make_new(char *begining, char *last)
{
	t_token *node = (t_token *)malloc(sizeof(t_token));
	if(is_dq(*begining))
		node->val = strdup(++begining, --last);
	else if (is_env(*begining))
		node->val = strdup(++begining, last);
	else
		node->val = strdup(begining, last);
	node->kind = get_kind(begining , last);
	node->next = NULL;
	return (node);
}

tokenize(char *line)
{
	t_token *head;
	t_token	*new;
	char *begining;
	char *last;

	begining = line;
	while(*begining != '\0')
	{
		last = get_last(begining);
		new = make_new(begining, last);
		add_last(head, new);
		begining = last++;
	}
}