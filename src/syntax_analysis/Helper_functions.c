/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:16:45 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/01 14:39:03 by moseddik         ###   ########.fr       */
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
		s1 = ft_calloc(1, sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
	}
	newstr = ft_calloc(1, (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2)));
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

t_token_list	*join_files(t_ast *node, t_token_list *token)
{
	if (!ft_strcmp(token->lexeme, "<") || !ft_strcmp(token->lexeme, ">")
		|| !ft_strcmp(token->lexeme, ">>"))
	{
		token->is_parsed = 1;
		if (node->cmd_node->redir_files == NULL)
			node->cmd_node->redir_files = ft_strdup(token->lexeme);
		else
			node->cmd_node->redir_files
				= ft_strjoin_char(node->cmd_node->redir_files,
					token->lexeme, ' ');
		token = token->next;
		node->cmd_node->redir_files
			= ft_strjoin_char(node->cmd_node->redir_files,
				token->lexeme, ' ');
		token->is_parsed = 1;
	}
	if (ft_strcmp(token->lexeme, "<<") == 0)
	{
		token->is_parsed = 1;
		token = token->next;
		if (token->heredoc_content)
			node->cmd_node->heredoc = ft_strdup(token->heredoc_content);
		token->is_parsed = 1;
	}
	return (token);
}

t_token_list	*get_next_to_parse(t_token_list *token)
{
	while (token && token->is_parsed != 0)
		token = token->next;
	return (token);
}
