/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:22:07 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 14:46:58 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_child(t_ast *node)
{
	char	**env;

	env = NULL;
	free(node->cmd_node->cmd_args);
	if (node->cmd_node->files != NULL)
		if (redirections(node) == false)
			exit(EXIT_FAILURE);
	if (!node->cmd_node->cmd_table)
		exit(EXIT_FAILURE);
	node->cmd_node->cmd_args = get_cmd(node);
	dup2(node->cmd_node->fdout, 1);
	dup2(node->cmd_node->fdin, 0);
	env = convert_envirenment(*node->cmd_node->m_env);
	execve(node->cmd_node->cmd_args, node->cmd_node->cmd_table, env);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("\x1b[31m Minshell : %s: command not found\n\x1b[0m",
		node->cmd_node->cmd_table[0]);
	exit(127);
}
