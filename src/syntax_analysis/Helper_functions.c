/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:16:45 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/28 20:14:40 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_char(char *s1, char const *s2, char c)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	newstr = (char *)malloc((sizeof(char)
				* (ft_strlen(s1) + ft_strlen(s2) + 2)));
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		newstr[i] = s1[i];
	free(s1);
	newstr[i++] = c;
	j = 0;
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}

void	join_cmd_args(t_ast *node, t_token_list *token)
{
	node->type = CMD;
	if (node->cmd_node->cmd_args == NULL)
		node->cmd_node->cmd_args = ft_strdup(token->lexeme);
	else
		node->cmd_node->cmd_args
			= ft_strjoin_char(node->cmd_node->cmd_args, token->lexeme, ' ');
}

void	join_files(t_ast *node, t_token_list *token)
{
	if (!ft_strcmp(token->lexeme, "<") || !ft_strcmp(token->lexeme, ">")
		|| !ft_strcmp(token->lexeme, ">>"))
	{
		if (node->cmd_node->redir_files == NULL)
			node->cmd_node->redir_files = ft_strdup(token->lexeme);
		else
			node->cmd_node->redir_files
				= ft_strjoin_char(node->cmd_node->redir_files,
					token->lexeme, ' ');
		node->cmd_node->redir_files
			= ft_strjoin_char(node->cmd_node->redir_files,
				token->next->lexeme, ' ');
	}
}

t_token_list	*get_next_operator(t_token_list *token_list)
{
	if (token_list == NULL || token_list->type == OPERATOR)
		return (token_list);
	if (token_list->type == LEFTPAREN)
	{
		token_list = skip_to_right_parentheses(token_list->next);
		if (token_list == NULL || token_list->type == OPERATOR)
			return (token_list);
	}
	return (get_next_operator(token_list->next));
}

t_token_list	*skip_to_right_parentheses(t_token_list *token)
{
	if (token == NULL)
		return (NULL);
	if (token->type == LEFTPAREN)
		token = skip_to_right_parentheses(token->next);
	if (token && token->type == RIGHTPAREN)
		return (token->next);
	if (token)
		return (skip_to_right_parentheses(token->next));
	return (NULL);
}
