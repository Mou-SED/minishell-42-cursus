/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_scan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:11:40 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 10:23:54 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	unclosed_quote(char *lexeme, char quote_type)
{
	if (*lexeme == '\0' && (quote_type == '"' || quote_type == '\''))
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

int	get_first_quote(char *lexeme, int index)
{
	if (*lexeme == '\0')
		return (0);
	else if (*lexeme == '\'' || *lexeme == '"')
		return (index);
	else
	{
		index++;
		return (get_first_quote(++lexeme, index));
	}
	return (index);
}

static bool	check_syntax_error_helper(t_token_list *token, int *error)
{
	if ((token->type != WORD && token->type != RIGHTPAREN
			&& token->type != REDIRECTION) && token->next == NULL)
		return (ft_print_error(token->lexeme), true);
	else if (token->type == WORD
		&& unclosed_quote(
			&token->lexeme[get_first_quote(token->lexeme, 0) + 1],
			token->lexeme[get_first_quote(token->lexeme, 0)]) == true)
		return (ft_print_error("unclosed_quote") , *error = 1, true); // TODO: Delete this line
	else if (token->next && !ft_strcmp(token->lexeme, "(")
		&& !ft_strcmp(token->next->lexeme, ")"))
		return (ft_print_error(token->next->lexeme), *error = 2, true);
	else if (token->next && (token->type == OPERATOR || token->type == PIPE)
		&& (token->next->type != WORD && token->next->type != LEFTPAREN
			&& token->next->type != REDIRECTION))
		return (ft_print_error(token->lexeme), true);
	else if (token->next && token->type == REDIRECTION
		&& token->next->type != WORD)
		return (ft_print_error(token->next->lexeme), true);
	return (false);
}

bool	check_syntax_error(t_token_list *token, int *i)
{
	int	error;

	*i = 0;
	error = 0;
	if (token->type != WORD && token->type != REDIRECTION
		&& token->type != LEFTPAREN)
		return (ft_print_error(token->lexeme), true);
	while (token != NULL)
	{
		if (token->type == LEFTPAREN)
			*i += 1;
		else if (token->type == RIGHTPAREN)
			*i -= 1;
		if (check_syntax_error_helper(token, &error) == true)
			break ;
		token = token->next;
	}
	if (*i != 0 && error != 2)
		printf("Minishell: Error: Unclosed 'Parenthèses'\n");
	else if (error == 1)
		*i = 1;
	return (true);
}