/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:13:22 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/05 22:04:33 by moseddik         ###   ########.fr       */
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

typedef struct s_token_list
{
	char				*lexeme;
	t_token_type		type;
	struct s_token_list	*next;
}	t_token_list;

char	*quote_case(char *str, t_token_list *token_ptr);
char	*pipe_case(char *str, t_token_list *token_ptr);
char	*word_case(char *str, t_token_list *token_ptr);
char	*operator_case(char *str, t_token_list *token_ptr);

void	tokenizer(char *cmd, t_token_list *head);

#endif