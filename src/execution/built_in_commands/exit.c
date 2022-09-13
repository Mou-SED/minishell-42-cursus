/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:03:18 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/13 22:13:18 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	normal_case(t_ast *node)
{
	int	i;

	i = 1;
	if (node->cmd_node->cmd_table[i] == NULL)
	{
		if (node->cmd_node->unused_pipe_fd == -1)
			write(2, "exit\n", 5);
		exit(g_status);
	}
}

void	execute_exit(t_ast *node)
{
	int	i;

	i = 1;
	normal_case(node);
	if (node->cmd_node->unused_pipe_fd == -1)
		write(2, "exit\n", 5);
	if (node->cmd_node->cmd_table[i + 1] != NULL
		&& ft_isnumber(node->cmd_node->cmd_table[i]) == true)
	{
		write(2, "Minishell: exit: too many arguments\n", 36);
		g_status = 1;
		return ;
	}
	if (ft_isnumber(node->cmd_node->cmd_table[i]) == false)
	{
		dup2(STDERR_FILENO, 1);
		printf("Minishell: exit: %s: numeric argument required\n",
			node->cmd_node->cmd_table[i]);
		exit(255);
	}
	exit(ft_atoi(node->cmd_node->cmd_table[i]));
}
