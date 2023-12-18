#include "execute.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	while (i + 1 < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

int	is_redir_token(int 	kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HERE_DOC 
		|| kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}

size_t strlcpy_from_list(char *dest, t_token *src, size_t n)
{
	size_t	dest_i;
	size_t	src_i;

	dest_i = 0;
	while(dest_i < n || src != NULL)
	{
		src_i = 0;
		while (src->val[src_i] != '\0')
		{
			dest[dest_i] = src->val[src_i];
			dest_i++;
			src_i++;
		}
		src = src->next;
	}
	return (dest_i);
}

int update_redir(t_token *redir_tokens)
{
	t_token	*ptr;
	t_token *start;
	size_t	count;

	start = redir_tokens->next;
	ptr = start->next;
	count = 0;
	while(ptr->next != NULL)
	{
		if (is_redir_token(ptr->kind))
		{
			char *str = (char *)malloc(sizeof(char) * count);
			if (strlcpy_from_list(str, start, count) != count)
				//error
			start = ptr;
			count = 0;
		}
		else
			count += ft_strlen(ptr->val);
		ptr = ptr->next;
	}
}