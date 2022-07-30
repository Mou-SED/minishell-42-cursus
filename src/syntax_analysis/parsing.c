/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:44:04 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/30 15:48:02 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_operator(t_ast *root, t_token_list *token)
{
	t_ast	*current_node;

	token->is_parsed = 1;
	current_node = ft_ast_new(token);
	if (ft_strcmp(token->lexeme, "&&") == 0)
		current_node->type = AND;
	else
		current_node->type = OR;
	current_node->left = root;
	current_node->right = parse_cmd(token->next);
	return (current_node);
}

t_ast	*parse_parenteses(t_ast *node, t_token_list *token)
{
	node->type = PAR;
	node->right = building_ast(NULL, token->next);
	return (node);
}

t_ast	*parse_pipe(t_ast *node, t_token_list *token)
{
	t_ast	*pipe_node;

	token->is_parsed = 1;
	pipe_node = ft_ast_new(token);
	pipe_node->type = PIP;
	pipe_node->left = node;
	pipe_node->right = parse_cmd(token->next);
	return (pipe_node);
}

t_ast	*parse_cmd(t_token_list *token)
{
	t_ast	*node;

	node = ft_ast_new(token);
	while (token != NULL && token->type != OPERATOR
		&& token->type != RIGHTPAREN)
	{
		token->is_parsed = 1;
		if (token->type == LEFTPAREN)
			node = parse_parenteses(node, token);
		if (token->type == PIPE)
			return (parse_pipe(node, token));
		if (token->type == REDIRECTION)
			token = join_files(node, token);
		else if (token->type == WORD)
			join_cmd_args(node, token);
		token = get_next_to_parse(token);
	}
	return (node);
}
