/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:47:46 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 19:54:39 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	syntax_error_helper(t_token_list *token)
{
	if (token->next && (token->type == OPERATOR || token->type == PIPE)
		&& (token->next->type != WORD && token->next->type != LEFTPAREN
			&& token->next->type != REDIRECTION))
		return (true);
	else if (token->next && !ft_strcmp(token->lexeme, "(")
		&& !ft_strcmp(token->next->lexeme, ")"))
		return (true);
	else if (token->type == REDIRECTION && token->next == NULL)
		return (ft_print_error("newline"), true);
	else if (token->next && token->type == REDIRECTION
		&& token->next->type != WORD)
		return (true);
	else if ((token->type != WORD && token->type != RIGHTPAREN
			&& token->type != REDIRECTION) && token->next == NULL)
		return (true);
	return (false);
}

bool	her_doc(t_token_list *token, int i, t_env *m_env)
{
	if (i != 0)
		return (true);
	if (token->type != WORD && token->type != REDIRECTION
		&& token->type != LEFTPAREN)
		return (true);
	while (token != NULL)
	{
		if (token->next && ft_strcmp(token->lexeme, "<<") == 0)
		{
			if (run_herdoc(token->next, m_env) == false)
				return (true);
		}
		if (syntax_error_helper(token) == true)
			return (true);
		token = token->next;
	}
	return (false);
}
