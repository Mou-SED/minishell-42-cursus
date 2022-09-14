/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:49:00 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/24 10:43:14 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*word_case(char *str, t_token_list *token_ptr)
{
	int		index;
	char	*ptr;

	index = 0;
	while (str[index] != '\0' && str[index] != ' ' && !is_token(&str[index]))
	{
		if (str[index] == '\'' || str[index] == '"')
			break ;
		index++;
	}
	token_ptr->lexeme = ft_calloc((index + 1), sizeof(char));
	ft_memcpy(token_ptr->lexeme, str, index);
	token_ptr->lexeme[index] = '\0';
	ptr = token_ptr->lexeme;
	if (str[index] == '\'' || str[index] == '"')
	{
		str = quote_case(str + index, token_ptr);
		token_ptr->lexeme = ft_strjoin(ptr, token_ptr->lexeme);
		free(ptr);
		index = 0;
	}
	token_ptr->type = WORD;
	return (str + index);
}

void	tokenizer(char *cmd, t_token_list **head)
{
	t_token_list	*next_token;

	if (*cmd == '\0')
		return ;
	if (*cmd == '(' || *cmd == ')')
		cmd = paren_case(cmd, *head);
	else if (*cmd == '\'' || *cmd == '"')
		cmd = quote_case(cmd, *head);
	else if (*cmd == '|' && *(cmd + 1) == '|')
		cmd = operator_case(cmd, *head);
	else if (*cmd == '&' && *(cmd + 1) == '&')
		cmd = operator_case(cmd, *head);
	else if (*cmd == '|')
		cmd = pipe_case(cmd, *head);
	else if (*cmd == '>' || *cmd == '<')
		cmd = redir_case(cmd, *head);
	else if (*cmd != ' ')
		cmd = word_case(cmd, *head);
	cmd = skip_space(cmd);
	if (*cmd != '\0')
	{
		next_token = ft_lstnew_token("next_token");
		ft_lstadd_token_back(head, next_token);
	}
	tokenizer(cmd, &next_token);
}
