/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:49:00 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/05 22:16:56 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_list	*ft_lstnew_token(char *content)
{
	t_token_list	*head;

	head = malloc(sizeof(t_token_list));
	if (!head)
		return (NULL);
	head->lexeme = content;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_token_back(t_token_list **alst, t_token_list *new)
{
	t_token_list	*ptr;

	if (alst == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		ptr = *alst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->next = NULL;
	}
}

int	is_token(char *str)
{
	if (*str == '|' || *str == '>' || *str == '<'
		|| (*str == '&' && *(str + 1) == '&'))
		return (1);
	return (0);
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
	while (str[index] != '\0' && str[index] != quote_type)
		index++;
	token_ptr->lexeme = malloc((index + 2) * sizeof(char));
	index = 0;
	token_ptr->lexeme[index++] = quote_type;
	while (str[index] != '\0' && str[index] != quote_type)
	{
		token_ptr->lexeme[index] = str[index];
		index++;
	}
	token_ptr->lexeme[index++] = quote_type;
	token_ptr->lexeme[index] = '\0';
	token_ptr->type = WORD;
	return (str + index);
}

char	*word_case(char *str, t_token_list *token_ptr)
{
	int		index;
	char	*ptr;

	index = 0;
	while (str[index] != '\0' && !is_token(&str[index]))
	{
		if (str[index] == 34 || str[index] == 39)
			break ;
		index++;
	}
	token_ptr->lexeme = malloc((index + 1) * sizeof(char));
	index = 0;
	while (str[index] != '\0' && !is_token(&str[index]))
	{
		if (str[index] == 34 || str[index] == 39)
			break ;
		token_ptr->lexeme[index] = str[index];
		index++;
	}
	token_ptr->lexeme[index] = '\0';
	ptr = token_ptr->lexeme;
	if (str[index] == 34 || str[index] == 39)
	{
		str = quote_case(str + index, token_ptr);
		token_ptr->lexeme = ft_strjoin(ptr, token_ptr->lexeme);
		index = 0;
	}
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

void	tokenizer(char *cmd, t_token_list *head)
{
	static int		value;
	t_token_list	*token_ptr;
	char			*buffer;

	if (value == 0)
	{
		head = ft_lstnew_token(cmd);
		token_ptr = head;
		value++;
	}
	if (*cmd == '\0')
		return ;
	else if (*cmd == 34 || *cmd == 39)
		buffer = quote_case(cmd, token_ptr);
	else if (*cmd == '|' && *(cmd + 1) == '|')
		buffer = operator_case(cmd, token_ptr);
	else if (*cmd == '&' && *(cmd + 1) == '&')
		buffer = operator_case(cmd, token_ptr);
	else if (*cmd == '|')
		buffer = pipe_case(cmd, token_ptr);
	else
		buffer = word_case(cmd, token_ptr);
	ft_lstadd_token_back(&token_ptr, ft_lstnew_token("content"));
	if (value != 0)
		token_ptr = token_ptr->next;
	tokenizer(buffer, token_ptr);
}
