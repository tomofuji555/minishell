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

void sepa_char (char *line, t_token *head)
{
	ssize_t	mv_count;

	mv_count = 0;
	while (*line != '\0')	
	{
		if (*line == ' ')	
			mv_count = space_token (line, head, *line)
		else if (*line == '<' || *line == '>')
			mv_count = redirect_token (line, head, *line);
		else if (*line == '|')
			mv_count = pipe_token (line, head, *line);	
		else if (*line == '$')
			mv_count = dollar_token (line, head, *line);
		else if (*line == '\'' || *line == '\"')
			mv_count = quort_token (line, head, *line);
		line = line + mv_count;
	}
}

t_token	*make_new_token(char *line, char mode)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->val = line;
	node->next = NULL;
	judge_token_type (mode);
	return (node);
}

void	make_token_list(char *line, t_token *head, char mode)
{
	char *str;
	
	str = ft_substr (line, 0, rt);
	token = make_new_token (str, mode);	
	
}

ssize_t	space_token(char *line, t_token *head)
{
	ssize_t	rt;

	rt = 0;
	while (*line == ' ')
	{
		rt++;
		line++;	
	}
	make_token_list (line, head);
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

