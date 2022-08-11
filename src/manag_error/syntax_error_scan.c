/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_scan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:11:40 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/10 11:38:36 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	unclosed_quote(char *lexeme, char quote_type)
{
	if (*lexeme == '\0' && quote_type != 0)
		return (true);
	else if (*lexeme == '\0')
		return (false);
	if (*lexeme == '\'' || *lexeme == '"')
	{
		if (*lexeme == quote_type)
			return (unclosed_quote(++lexeme, 0));
		else if (quote_type == 0)
			return (unclosed_quote(&lexeme[1], *lexeme));
		else
			return (unclosed_quote(&lexeme[1], quote_type));
	}
	else
		return (unclosed_quote(++lexeme, quote_type));
}

static int	get_first_quote(char *lexeme, int *index)
{
	if (*lexeme == '\0')
		return (0);
	else if (*lexeme == '\'' || *lexeme == '"')
		return (*index);
	else
	{
		(*index)++;
		return (get_first_quote(++lexeme, index));
	}
	return (*index);
}

static bool	check_syntax_error_helper(t_token_list *token)
{
	int	index;

	index = 0;
	if ((token->type != WORD && token->type != RIGHTPAREN
			&& token->type != REDIRECTION) && token->next == NULL)
		return (ft_print_error(token->lexeme), true);
	else if (token->type == WORD
		&& unclosed_quote(
			&token->lexeme[get_first_quote(token->lexeme, &index) + 1],
			token->lexeme[index]) == true)
		return (ft_print_error("unclosed_quote"), true);
	else if (token->next && !ft_strcmp(token->lexeme, "(") && !ft_strcmp(token->next->lexeme, ")"))
		return (ft_print_error(token->next->lexeme), true);
	else if (token->next && (token->type == OPERATOR || token->type == PIPE)
		&& (token->next->type != WORD && token->next->type != LEFTPAREN
			&& token->next->type != REDIRECTION))
		return (ft_print_error(token->lexeme), true);
	else if (token->next && token->type == REDIRECTION
		&& token->next->type != WORD)
			return (ft_print_error(token->next->lexeme), true);
	return (false);
}

bool	check_syntax_error(t_token_list *token)
{
	if (token->type != WORD && token->type != REDIRECTION
		&& token->type != LEFTPAREN)
		return (ft_print_error(token->lexeme), true);
	while (token != NULL)
	{
		if (check_syntax_error_helper(token))
			break ;
		token = token->next;
	}
	return (true);
}

bool	check_empty_parenthesis(t_ast *root)
{
	if (root == NULL)
		return (false);
	else if (root->type == PAR && (root->right == NULL
			|| root->right->type == PAR))
		return (true);
	else
		return (check_empty_parenthesis(root->left)
			&& check_empty_parenthesis(root->right));
}
