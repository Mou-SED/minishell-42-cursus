/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:58:01 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/14 14:53:42 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*redir_case(char *str, t_token_list *token_ptr)
{
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			token_ptr->lexeme = ft_strdup(">>");
		else
			token_ptr->lexeme = ft_strdup(">");
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			token_ptr->lexeme = ft_strdup("<<");
		else
			token_ptr->lexeme = ft_strdup("<");
	}
	token_ptr->type = REDIRECTION;
	return (str + ft_strlen(token_ptr->lexeme));
}

char	*pipe_case(char *str, t_token_list *token_ptr)
{
	token_ptr->lexeme = ft_strdup("|");
	token_ptr->type = PIPE;
	return (++str);
}

char	*quote_case(char *str, t_token_list *token_ptr)
{
	char	quote_type;
	int		index;

	index = 0;
	quote_type = str[index++];
	while (str[index] != '\0')
	{
		if ((str[index] == ' ' || is_token(&str[index]) == 1)
			&& quote_type == 0)
			break ;
		else if (str[index] == '\'' || str[index] == '"')
		{
			if (str[index] == quote_type)
				quote_type = 0;
			else if (quote_type == 0)
				quote_type = str[index];
		}
		index++;
	}
	token_ptr->lexeme = ft_calloc((index + 1), sizeof(char));
	ft_memcpy(token_ptr->lexeme, str, index);
	token_ptr->lexeme[index] = '\0';
	token_ptr->type = WORD;
	return (str + index);
}


char	*operator_case(char *str, t_token_list *token_ptr)
{
	if (*str == '|')
		token_ptr->lexeme = ft_strdup("||");
	else
		token_ptr->lexeme = ft_strdup("&&");
	token_ptr->type = OPERATOR;
	return (str + 2);
}

char	*paren_case(char *str, t_token_list *token_ptr)
{
	int	index;

	index = -1;
	if (str[++index] == ')')
	{
		token_ptr->lexeme = ft_calloc(2, sizeof(char));
		token_ptr->lexeme[index++] = ')';
		token_ptr->lexeme[index] = '\0';
		token_ptr->type = RIGHTPAREN;
	}
	else if (str[index] == '(')
	{
		token_ptr->lexeme = ft_calloc(2, sizeof(char));
		token_ptr->lexeme[index++] = '(';
		token_ptr->lexeme[index] = '\0';
		token_ptr->type = LEFTPAREN;
	}
	return (str + index);
}
