/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:03:18 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/22 19:02:34 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_exit(t_ast *node)
{
	int	i;

	i = 1;
	if (node->cmd_node->files != NULL)
		if (redirections(node) == false)
			return ;
	if (node->cmd_node->cmd_table[i] == NULL)
	{
		if (node->cmd_node->unused_pipe_fd == -1)
			write(2, "exit\n", 5);
		exit(status);
	}
	if (node->cmd_node->cmd_table[i + 1] != NULL)
	{
		write(2, "Minishell: exit: too many arguments\n", 36);
		status = 1;
		return ;
	}
	if (ft_isnumber(node->cmd_node->cmd_table[i]) == false)
	{
		write(2, "Minishell: exit: numeric argument required\n", 44);
		exit(255);
	}
	if (node->cmd_node->unused_pipe_fd == -1)
		write(2, "exit\n", 5);
	exit(ft_atoi(node->cmd_node->cmd_table[i]));
}
