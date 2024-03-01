/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:19:04 by toshi             #+#    #+#             */
/*   Updated: 2024/03/02 03:26:07 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static size_t _strlen_env_expanded(char *str)
{
	size_t len;
	char *env_val;

	len = 0;
	while(*str)
	{
		if (*str == '$' && count_envname(str))
		{
			env_val = search_env_val(str, count_envname(str));
			if (env_val)
				len += ft_strlen(env_val);
			str += (sizeof(char) * (count_envname(str)));
		}
		else
			len++;
		str++;
	}
	return (len);
}

static size_t _strlcat_env_expanded(char *dest, char *str, size_t len)
{
	size_t dest_i;
	char *env_val;

	dest_i = 0;
	while(*str && dest_i < len)
	{
		if(*str == '$' && count_envname(str))
		{
			env_val = search_env_val(str, count_envname(str));
			if (env_val)
				dest_i += ft2_strlcat(dest, env_val, len);
			str += (sizeof(char) * (count_envname(str)));
		}
		else
			dest[dest_i++] = *str;
		str++;
	}
	dest[dest_i] = '\0';
	return (dest_i);
}

//文字列にENVが見つかれば、引数のstrをfreeして、新しいstringを返す
char	*expand_env_in_dquote(char *str)
{
	size_t expanded_len;
	char *expanded_str;

	if (str == NULL)
		return (NULL);
	expanded_len = _strlen_env_expanded(str);
	if (expanded_len  == ft_strlen(str))
		return (str);
	expanded_str = (char *)ft_xmalloc(sizeof(char) * (expanded_len + 1));
	_strlcat_env_expanded(expanded_str, str, (expanded_len + 1));
	free(str);
	return (expanded_str);
}

/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static size_t count_untill_last_and_set_kind(char *begining, enum e_token_kind *kind)
{
	ssize_t	i;

	if (is_ifs(*begining))
	{
		*kind = TKN_SPACE;
		return (count_untill_ifs_last(begining));
	}
	else
	{
		*kind = TKN_TEXT;
		i = 1;
		while(begining[i] && !is_ifs(begining[i]))
			i++;
		return (i);
	}
}

static t_token *tokenize_space_or_text(char *env_val)
{
	t_token 			*head;
	t_token				*new;
	ssize_t				count;
	enum e_token_kind	kind;

	if (env_val == NULL)
		return (NULL);
	head = NULL;
	while(*env_val)
	{
		count = count_untill_last_and_set_kind(env_val, &kind);
		new = make_new_tkn(env_val, count, kind);
		add_tkn_last(&head, new);
		env_val += count;
	}
	return (head);
}

static t_token	*expand_env_of_tkn(t_token **dest_head, t_token *env_tkn, t_token *prev)
{
	t_token *expanded_head;
	t_token *next_ptr;

	expanded_head = tokenize_space_or_text(search_env_val(env_tkn->val, count_envname(env_tkn->val)));
	next_ptr = env_tkn->next;
	if (expanded_head == NULL)
	{
		if (prev == NULL)
			*dest_head = next_ptr;
		else
			prev->next = next_ptr;
	}
	else
	{
		if (prev == NULL)
			*dest_head = expanded_head;
		else
			prev->next = expanded_head;
		find_last_tkn(expanded_head)->next = next_ptr;
	}
	free_tkn(env_tkn);
	return (next_ptr);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

//引数を**型にしないと反映されない
//syntaxは保証されている前提で実装
void	expansion_tkn_lst(t_token **tkn_head)
{
	t_token *tkn_ptr;

	tkn_ptr = *tkn_head;
	while(tkn_ptr != NULL)
	{
		if (tkn_ptr->kind == TKN_HEREDOC)
			tkn_ptr = find_last_valuable_tkn(tkn_ptr->next)->next;
		else if (tkn_ptr->kind == TKN_ENV)
			tkn_ptr = expand_env_of_tkn(tkn_head, tkn_ptr, find_prev_tkn(*tkn_head, tkn_ptr));
		else
		{
			if (tkn_ptr->kind == TKN_D_QUOTE)
				tkn_ptr->val = expand_env_in_dquote(tkn_ptr->val);
			tkn_ptr = tkn_ptr->next;
		}
	}
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static size_t count_arg_strs(t_token *tkn_ptr)
{
	size_t i;

	i = 0;
	while (tkn_ptr != NULL)
	{
		if (is_valuable_tkn(tkn_ptr->kind))
		{
			i++;
			tkn_ptr = find_last_valuable_tkn(tkn_ptr);
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (i);
}

//valuable_tknが一つもないtkn_lstはNULLに変換される
char **make_cmd_args(t_token *tkn_head)
{
	char **cmd_args;
	size_t i;
	t_token *tkn_ptr;
	t_token *last;

	size_t count = count_arg_strs(tkn_head);
	if (count == 0)
		return (NULL);
	cmd_args = (char **)ft_xmalloc(sizeof(char *) * (count + 1));
	i = 0;
	tkn_ptr = tkn_head;
	while(tkn_ptr != NULL)
	{
		if (is_valuable_tkn(tkn_ptr->kind))
		{
			last = find_last_valuable_tkn(tkn_ptr);
			cmd_args[i++] = substr_from_tkn(tkn_ptr, last);
			tkn_ptr = last;
		}
		tkn_ptr = tkn_ptr->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

static t_redir	*find_last_redir(t_redir *head)
{
	t_redir	*ptr;

	ptr = head;
	while(ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static void	add_redir_last(t_redir **head_node, t_redir *new_node)
{
	if (*head_node == NULL)
	{
		*head_node = new_node;
		return;
	}
	find_last_redir(*head_node)->next = new_node;
}

static t_bool	has_space_between(t_token *begining)
{
	t_token *ptr;
	t_token *prev;

	ptr = begining->next;
	prev = begining;
	while (ptr && !is_redir_tkn(ptr->kind))
	{
		if (is_valuable_tkn(prev->kind) && ptr->kind == TKN_SPACE && \
			ptr->next != NULL && is_valuable_tkn(ptr->next->kind))
			return (TRUE);
		prev = ptr;
		ptr = ptr->next;
	}
	return (FALSE);
}

static t_bool	contains_quote(t_token *begining)
{
	t_token *ptr;

	ptr = begining->next;
	while (ptr && !is_redir_tkn(ptr->kind))
	{
		if (ptr->kind == TKN_S_QUOTE || ptr->kind == TKN_D_QUOTE)
			return (TRUE);
		ptr = ptr->next;
	}
	return (FALSE);
}

static enum e_redir_kind	convert_redir_kind(t_token *begining)
{
	//if (has_space_between(begining))
	//	return (AMBIGUOUS_REDIR);
	if (begining->kind == TKN_IN_FILE)
		return (REDIR_IN_FILE);
	else if (begining->kind == TKN_HEREDOC)
	{
		if (contains_quote(begining))
			return (REDIR_HEREDOC_NO_EXPAND);
		else
			return (REDIR_HEREDOC);
	}
	else if (begining->kind == TKN_OUT_FILE)
		return (REDIR_OUT_FILE);
	else
		return (REDIR_APPEND_FILE);
}

//char *clean_space()

//リダイレクトのvalがifsのみだと、空文字列("")が入る
static t_redir	*make_new_redir(t_token *begining, t_token *last)
{
	t_redir	*node;
	char *tmp_val;
	char *tmp_val_2;

	node = (t_redir *)ft_xmalloc(sizeof(t_redir));
	node->kind = convert_redir_kind(begining);
	tmp_val =  substr_from_tkn(begining->next, last);
	node->val =  ft_xstrtrim(tmp_val, " \t\n");
	free(tmp_val);
	node->next = NULL;
	return (node);
}

t_redir	*make_redir_lst(t_token *tkn_ptr)
{
	t_redir	*head;
	t_redir *new;
	t_token	*tkn_begining;

	if (tkn_ptr == NULL)
		return (NULL);
	head = NULL;
	tkn_begining = tkn_ptr;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_tkn(tkn_ptr->next->kind))
		{
			new = make_new_redir(tkn_begining, tkn_ptr);
			add_redir_last(&head, new);
			tkn_begining = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (head);
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */

void	expansion(t_tree_node *ptr)
{
	while(ptr != NULL)
	{
		expansion_tkn_lst(&ptr->init_data.cmd_tokens);
		expansion_tkn_lst(&ptr->init_data.infile_tokens);
		expansion_tkn_lst(&ptr->init_data.outfile_tokens);
		ptr->exec_data.cmd_args = make_cmd_args(ptr->init_data.cmd_tokens);
		ptr->exec_data.infile_paths = make_redir_lst(ptr->init_data.infile_tokens);
		ptr->exec_data.outfile_paths = make_redir_lst(ptr->init_data.outfile_tokens);
		ptr = ptr->right;
	}
}
/* --------------------------------------------------------- */
/* --------------------------UNTIL-------------------------- */
/* --------------------------------------------------------- */
