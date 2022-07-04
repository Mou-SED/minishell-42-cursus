/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:13:22 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/04 19:52:58 by zaabou           ###   ########.fr       */
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
	struct s_token  *next;
}	t_token;

t_token	*quote_case(char *str);

#endif