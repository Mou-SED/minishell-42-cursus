/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:07:37 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/29 19:19:27 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_list	*get_next_to_parse(t_token_list *token)
{
	while (token && token->is_parsed != 0)
		token = token->next;
	return (token);
}
t_ast	*ft_ast_new(t_token_list	*token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (node == NULL)
		exit(EXIT_FAILURE);
	if (token->type !=  OPERATOR)
	{
		node->cmd_node = ft_calloc(1, sizeof(t_cmd));
		if (node->cmd_node == NULL)
			exit(EXIT_FAILURE);
	}
	return (node);
}

t_ast	*building_ast(t_ast *root, t_token_list *token)
{
	if (token == NULL || token->type == RIGHTPAREN)
		return (root);
	if (token->type == OPERATOR)
		root = parse_operator(root, token);
	else
		root = parse_cmd(token);
	token = get_next_to_parse(token);
	return (building_ast(root, token));
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
			free(root->cmd_node->cmd_table);
		if (root->cmd_node->cmd_args)
			free(root->cmd_node->cmd_args);
		if (root->cmd_node->redir_files)
			free(root->cmd_node->redir_files);
		free(root->cmd_node);
	}
	free(root);
	root = NULL;
}
