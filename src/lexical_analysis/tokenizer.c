/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:49:00 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/08 12:02:38 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*word_case(char *str, t_token_list *token_ptr)
{
	int		index;
	char	*ptr;

	index = 0;
	while (str[index] != '\0' && !is_token(&str[index]))
	{
		if (str[index] == '\'' || str[index] == '"')
			break ;
		index++;
	}
	token_ptr->lexeme = malloc((index + 1) * sizeof(char));
	index = 0;
	while (str[index] != '\0' && str[index] != ' ' && !is_token(&str[index]))
	{
		if (str[index] == '\'' || str[index] == '"')
			break ;
		token_ptr->lexeme[index] = str[index];
		index++;
	}
	token_ptr->lexeme[index] = '\0';
	ptr = token_ptr->lexeme;
	if (str[index] == '\'' || str[index] == '"')
	{
		str = quote_case(str + index, token_ptr);
		token_ptr->lexeme = ft_strjoin(ptr, token_ptr->lexeme);
		index = 0;
	}
	token_ptr->type = WORD;
	return (str + index);
}

void	tokenizer(char *cmd, t_token_list **head)
{
	char			*buffer;
	t_token_list	*add_newtoken;
	static int		value;

	add_newtoken = ft_lstnew_token("newline");
	if (value == 0)
	{
		*head = ft_lstnew_token("content");
		value++;
	}
	if (*cmd == '\0')
	{
		free(add_newtoken);
		add_newtoken = NULL;
		return ;
	}
	else if (*cmd == ' ')
	{
		free(add_newtoken);
		add_newtoken = *head;
		buffer = skip_space(cmd);
	}
	else if (*cmd == '(' || *cmd == ')')
		buffer = paren_case(cmd, *head);
	else if (*cmd == '\'' || *cmd == '"')
		buffer = quote_case(cmd, *head);
	else if (*cmd == '|' && *(cmd + 1) == '|')
		buffer = operator_case(cmd, *head);
	else if (*cmd == '&' && *(cmd + 1) == '&')
		buffer = operator_case(cmd, *head);
	else if (*cmd == '|')
		buffer = pipe_case(cmd, *head);
	else if (*cmd == '>' || *cmd == '<')
		buffer = redir_case(cmd, *head);
	else
		buffer = word_case(cmd, *head);
	ft_lstadd_token_back(head, add_newtoken);
	tokenizer(buffer, &add_newtoken);
}
