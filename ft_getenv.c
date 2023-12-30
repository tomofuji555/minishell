/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:13:06 by toshi             #+#    #+#             */
/*   Updated: 2023/12/31 00:13:07 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*ft_getenv(const char *target_str)
{
	extern char	**environ;
	char		*env_name;
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
	{
		env_name = ft_substr(environ[i], 0, (size_t)(ft_strchr(environ[i], '=') - environ[i]));
		if (ft_strcmp(env_name, target_str) == 0)
		{
			free(env_name);
			return (ft_strchr(environ[i], '=') + sizeof(char));
		}
		free(env_name);
		i++;
	}
	return (NULL);
}