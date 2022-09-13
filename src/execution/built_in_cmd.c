/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:53:27 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/13 15:44:48 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unused_pipe(t_ast *node)
{
	if (node->cmd_node->unused_pipe_fd != -1)
		close(node->cmd_node->unused_pipe_fd);
}

bool	check_if_built_in(t_ast *node)
{
	if (!ft_strcmp("echo", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("ECHO", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("unset", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("cd", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("export", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("env", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("ENV", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("exit", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("pwd", node->cmd_node->cmd_table[0])
		|| !ft_strcmp("PWD", node->cmd_node->cmd_table[0]))
		return (true);
	return (false);
}

void	execute_built_in(t_ast *node, char **cwd, int error_files)
{
	int	stdo;
	int	stin;

	if (error_files == 1)
	{
		g_status = 1;
		return ;
	}
	unused_pipe(node);
	stdo = dup(1);
	stin = dup(0);
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "echo")
		|| !ft_strcmp(node->cmd_node->cmd_table[0], "ECHO"))
		execute_echo(node);
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "PWD")
		|| !ft_strcmp(node->cmd_node->cmd_table[0], "pwd"))
		execute_pwd(node, &(*cwd));
	check_more_built_in(node, &(*cwd));
	(close(node->cmd_node->fdin), close(node->cmd_node->fdout));
	(dup2(stdo, 1), dup2(stin, 0));
	(close(stin), close(stdo));
}

void	check_more_built_in(t_ast *node, char **cwd)
{
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "exit"))
		execute_exit(node);
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "unset"))
		execute_unset(node);
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "env")
		|| !ft_strcmp(node->cmd_node->cmd_table[0], "ENV"))
		execute_env(node);
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "export"))
		execute_export(node);
	if (!ft_strcmp(node->cmd_node->cmd_table[0], "cd"))
		execute_cd(node, &(*cwd));
}
