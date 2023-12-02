/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofujiwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2023/12/02 16:20:57 by tofujiwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}	t_bool;

enum e_state
{
	STATE_SPACE,	
	STATE_TEXT,
	STATE_S_QUOTE,
	STATE_D_QUOTE,
	STATE_REDIRECT,	
};

enum e_token_type
{
	TOKEN_SPACE,
	TOKEN_TEXT,
	TOKEN_S_QUOTE, 
	TOKEN_D_QUOTE,
	TOKEN_DOLLAR,
	TOKEN_REDIRECT,
	TOKEN_PIPE,
};

enum e_chunk_type
{
	CHUNK_SPACE,
	CHUNK_TEXT, 
	CHUNK_ENV,
	CHUNK_IN_FILE,
	CHUNK_HERE_DOC,
	CHUNK_OUT_FILE,
	CHUNK_APPEND_FILE,
	PIPE,
};

typedef struct 
{
	enum e_token_type	token_type;
	char				*val;
	t_bool				last_token_flag;
}	t_token;

typedef struct
{
	enum e_chunk_type	chunk_type;
	t_token				*tokens;
	t_bool				last_chunk_flag;
}	t_chunk;

#endif
