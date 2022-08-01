/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:41:52 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/01 14:45:02 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_herdoc(t_token_list *token)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("> ");
		if ((token && heredoc && ft_strcmp(heredoc, token->lexeme) == 0))
			break ;
		else if (heredoc != NULL && *heredoc != 0)
			token->heredoc_content
				= ft_strjoin_char(token->heredoc_content, heredoc, '\n');
		else if (heredoc == NULL)
			break ; // TODO: Use global variable for exit status
		free(heredoc);
	}
	free(heredoc);
}

bool	her_doc(t_token_list *token)
{
	while (token != NULL)
	{
		if (token->next && ft_strcmp(token->lexeme, "<<") == 0)
			run_herdoc(token->next);
		else if (token->next && (token->type == OPERATOR || token->type == PIPE)
			&& (token->next->type != WORD && token->next->type != LEFTPAREN
				&& token->next->type != REDIRECTION))
			return (true);
		else if (token->next && token->type == REDIRECTION
			&& token->next->type != WORD)
			return (true);
		else if (token->type == REDIRECTION && token->next == NULL)
			return (ft_print_error("newline"), true);
		token = token->next;
	}
	return (false);
}
