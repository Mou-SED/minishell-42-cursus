/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:49:00 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/07 05:27:57 by zaabou           ###   ########.fr       */
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

char	*is_space(char *str)
{
	while (*str != '\0' && *str != ' ')
		str++;
	if (*str == ' ')
		str++;
	return (str);
}

char	*redir_case(char *str, t_token_list *token_ptr)
{
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			token_ptr->lexeme = strdup(">>");
		else
			token_ptr->lexeme = strdup(">");
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			token_ptr->lexeme = strdup("<<");
		else
			token_ptr->lexeme = strdup("<");
	}
	token_ptr->type = REDIRECTION;
	return (str + ft_strlen(token_ptr->lexeme));
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
	while (str[index] != '\0')
	{
		if (str[index] == quote_type)
		{
			if (str[++index] == ' ' || str[index] == '\0')
				break ;
			if (str[index] == '\'' || str[index] == '"')
				quote_type = str[index];
		}
		index++;	
	}
	token_ptr->lexeme = malloc((index + 1) * sizeof(char));
	ft_memcpy(token_ptr->lexeme, str, index);
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

char	*operator_case(char *str, t_token_list *token_ptr)
{
	if (*str == '|')
		token_ptr->lexeme = ft_strdup("||");
	else
		token_ptr->lexeme = ft_strdup("&&");
	token_ptr->type = OPERATOR;
	return (str + 2);
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
	if (*cmd == '\0')// TODO: free
	{
		free(add_newtoken);
		add_newtoken = NULL;
		return ;
	}
	else if (*cmd == ' ')
	{
		free(add_newtoken);
		add_newtoken = *head;
		buffer = is_space(cmd);
	}
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
