/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:07:37 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/28 19:41:38 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	{
		root = parse_operator(root, token);
		if (token->type == LEFTPAREN)
			token = skip_to_right_parentheses(token->next->next);
		else
			token = get_next_operator(token->next);
	}
	else
	{
		root = parse_cmd(token);
		printf("ROOT : %u\n", root->type);
		if (root->type == PAR)
			return (root);
		else
			token = get_next_operator(token);
	}
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
