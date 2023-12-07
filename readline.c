#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*head;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		// TODO: intepret line as a command
				
		free(line);
	}
	exit(0);
}

void split_to_token (char *line, t_token *head)
{
	ssize_t	mv_count;

	mv_count = 0;
	while (*line != '\0')	
	{
    if (*line == ' ')	
			mv_count = space_token (line, head);
    else if (*line == '<' || *line == '>')
      mv_count = redirect_token (line, head);
    //else if (*line == '<' && *(line + 1) == '<')
    //  mv_count = heredoc_token (line, head);
    //else if (*line == '>' && *(line + 1) == '>')
    //  mv_count = append_token (line, head);
    //else if (*line == '<')
		//	mv_count = infile_token (line, head);
    //else if (*line == '>')
    //  mv_count = outfile_token (line, head);
    else if (*line == '|')
			mv_count = pipe_token (line, head);
    else if (*line == '$')
			mv_count = env_token ( line, head);
    else if (*line == '\'' || *line == '\"')
			mv_count = quort_token (line, head);
    else
      mv_count = text_token (line, head);
		line = line + mv_count;
	}
}

void	judge_token_type(t_token **node, char char1, char char2)
{
  if (char1 == ' ')
    (*node)->token_type = TKN_SPACE;
  else if (char1 == '<' && char2 == '<')
    (*node)->token_type = TKN_HERE_DOC;
  else if (char1 == '>' && char2 == '>')
    (*node)->token_type = TKN_APPEND_FILE;
  else if (char1 == '<')
		(*node)->token_type = TKN_IN_FILE;
  else if (char1 == '>')
    (*node)->token_type = TKN_OUT_FILE;  
  else if (char1 == '|')
		(*node)->token_type = TKN_PIPE;
  else if (char1 == '$')
		(*node)->token_type = TKN_ENV;
  else if (char1 == '\'')
		(*node)->token_type = TKN_S_QUOTE;
  else if (char1 == '\"')
		(*node)->token_type = TKN_D_QUOTE;
  else	
		(*node)->token_type = TKN_TEXT;	
}

t_token	*make_new_token(char *line, t_token *head, ssize_t mv_count)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
  node->val = ft_substr (line, 0, mv_count); 
	node->next = NULL;
	judge_token_type (&node, *line, *(line + 1));  
	return (node);
}

void	make_token_list(char *line, t_token *head, char mode, ssize_t mv_count)
{
	char    *str;
  t_token *token;
	
//	str = ft_substr (line, 0, mv_count);
	token = make_new_token (line, head, mv_count);	
	
}

ssize_t	space_token(char *line, t_token *head, char mode)
{
	ssize_t	rt;

	rt = 0;
	while (*line == ' ')
	{
		rt++;
		line++;	
	}
	make_token_list (line, head, mode, rt);
	return (rt);
}

ssize_t	redirect_token(char *line, t_token *head)
{

}

ssize_t	pipe_token(char *line, t_token *head)
{

}

ssize_t	dollar_token(char *line, t_token *head)
{

}

ssize_t	quort_token(char *line, t_token *head, char line)
{

}

