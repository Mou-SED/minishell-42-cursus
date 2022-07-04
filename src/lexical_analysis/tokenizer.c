/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:49:00 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/04 20:25:42 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int		not_token(char *str)
// {
// 	if (*str == '|' || *str == '>' || *str == '<' || (*str == '&' && *(str + 1) == '&'))
// 		return (1);
// 	return (0);
// }

// char	*pipe_case(char *str)
// {
// 	t_token	*token_ptr;
	
// 	token_ptr = malloc(sizeof(t_token));
// 	token_ptr->lexeme = strdup("|");
// 	token_ptr->type = PIPE;
// 	lst_add_back(head, token_ptr);
// 	return (str + 1);
// }

t_token	*quote_case(char *str)
{
	t_token	*token_ptr;
	char	quote_type;
	int		index;

	index = 0;
	quote_type = str[index++];
	token_ptr = malloc(sizeof(t_token));
	while (str[index] != '\0' && str[index]  != quote_type)
		index++;
	token_ptr->lexeme = malloc((index + 2) * sizeof(char));
	index = 0;
	token_ptr->lexeme[index++] = quote_type;
	while (str[index] != '\0' && str[index]  != quote_type)
	{
		token_ptr->lexeme[index] = str[index];
		index++;
	}
	token_ptr->lexeme[index++] = quote_type;
	token_ptr->lexeme[index++] = '\0';
	token_ptr->type = WORD;
	return (token_ptr);
}

// char	*word_case(char *str)
// {
// 	int i = 0;
// 	t_token	*token_ptr;
// 	token_ptr = malloc(sizeof(t_token));
// 	while (str[i] != '\0' && str[i] != ' ' && not_token(str[i]))
// 		i++;
// 	ptr->content->lexeme = malloc((i * sizeof(char)) + 1);
// 	i = 0;
// 	while (str[i] != '\0' && not_token(str[i]))
// 	{
// 		ptr->content->lexeme[i] = str[i];
// 		i++;
// 	}
// 	ptr->content->lexeme[i] = '\0';
// 	ptr->content->type = WORD;
// 	ft_lstadd_back(head, ptr);
// 	return (str + i);
// }

// void	operator_case(char str);
// {
// 	t_token	*token_ptr;
// 	t_token_list *ptr = ft_lstnew(token_ptr);
// 	if (*operator == '|')
// 		ptr->content->lexeme = strdup("||");
// 	else
// 		ptr->content->lexeme = strdup("&&");
// 	ptr->content->type = OPERATOR;
// 	ft_lstadd_back(head, ptr);
// 	return (str + 2);
		
		
// }
	
// void	tokenizer(char *cmd, t_token_list **head)
// {
// 	if (*cmd == '\0')
// 		return ;
// 	else if (*cmd == 34 || *cmd == 39)
// 		cmd = quote_case(cmd);
// 	else if (*cmd == '|' && *(cmd + 1) == '|')
// 		cmd = operator_token(cmd);
// 	else if (*cmd == '&' && *(cmd + 1) == '&')
// 		cmd = operator_token(cmd);
// 	else if (*cmd == '|')
// 		cmd = pipe_token(cmd);
// 	else
// 		cmd = dup_word(cmd);
// 	tokenizer(cmd, head);
// }

