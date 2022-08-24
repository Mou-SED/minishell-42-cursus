/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:16:45 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/24 10:44:44 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_files(t_lst **head, t_lst *new)
{
	t_lst	*tmp;

	tmp = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*ft_strjoin_char(char *s1, char const *s2, char c)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	if (s1 == NULL)
		s1 = ft_calloc(1, sizeof(char) * 1);
	newstr = ft_calloc(1, (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2)));
	i = -1;
	while (s1[++i] != '\0')
		newstr[i] = s1[i];
	newstr[i++] = c;
	j = 0;
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	free(s1);
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
	t_lst	*tmp;

	tmp = NULL;
	if (!ft_strcmp(token->lexeme, ">>") || !ft_strcmp(token->lexeme, ">")
		|| !ft_strcmp(token->lexeme, "<") || !ft_strcmp(token->lexeme, "<<"))
	{
		tmp = ft_calloc(1, sizeof(t_lst));
		token->is_parsed = 1;
		if (ft_strcmp(token->lexeme, ">") == 0)
			tmp->mode = W_TRUNC;
		else if (ft_strcmp(token->lexeme, ">>") == 0)
			tmp->mode = W_APPRND;
		else if (ft_strcmp(token->lexeme, "<") == 0)
			tmp->mode = READ;
		else if (ft_strcmp(token->lexeme, "<<") == 0)
			tmp->mode = READ;
		token = token->next;
		token->is_parsed = 1;
		tmp->filename = ft_strdup(token->lexeme);
		add_files(&node->cmd_node->files, tmp);
	}
	return (token);
}

t_token_list	*get_next_to_parse(t_token_list *token)
{
	while (token && token->is_parsed != 0)
		token = token->next;
	return (token);
}
