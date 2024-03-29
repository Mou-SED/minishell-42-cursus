/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:07:37 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/24 10:43:37 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lst_clear(t_lst *files)
{
	t_lst	*tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp->filename);
		free(tmp);
	}
}

t_ast	*ft_ast_new(t_token_list	*token, t_env **m_env)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (token && token->type != OPERATOR)
	{
		node->type = CMD;
		node->cmd_node = ft_calloc(1, sizeof(t_cmd));
		node->cmd_node->m_env = m_env;
		node->cmd_node->fdin = 0;
		node->cmd_node->fdout = 1;
		node->cmd_node->unused_pipe_fd = -1;
		node->cmd_node->wait = false;
	}
	return (node);
}

t_ast	*building_ast(t_ast *root, t_token_list *token, t_env **m_env)
{
	if (token == NULL || token->type == RIGHTPAREN)
	{
		if (token && token->type == RIGHTPAREN)
			token->is_parsed = 1;
		return (root);
	}
	if (token->type == OPERATOR)
		root = parse_operator(root, token, m_env);
	else
		root = parse_cmd(token, m_env);
	token = get_next_to_parse(token);
	return (building_ast(root, token, m_env));
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
	table = NULL;
}

void	clear_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	if (root->left)
		clear_ast(root->left);
	if (root->right)
		clear_ast(root->right);
	if (root->cmd_node)
	{
		if (root->cmd_node->cmd_table)
			free_table(root->cmd_node->cmd_table);
		if (root->cmd_node->files)
			lst_clear(root->cmd_node->files);
		if (root->cmd_node->paths)
			free(root->cmd_node->paths);
		if (root->cmd_node->cmd_args)
			free(root->cmd_node->cmd_args);
		free(root->cmd_node);
	}
	free(root);
	root = NULL;
}
