/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:13:22 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/03 16:37:46 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "minishell.h"

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIRECTION,
	OPERATOR
}	t_token_type;

typedef struct s_token
{
	char			*lexeme;
	t_token_type	type;
}	t_token;

typedef t_list	t_token_list;

#endif