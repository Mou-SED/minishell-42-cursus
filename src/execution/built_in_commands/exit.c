/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:03:18 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/20 14:36:47 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_exit(t_ast *node)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (node->cmd_node->files != NULL)
		if (redirections(node) == false)
			return ;
	if (node->cmd_node->cmd_table[i] == NULL)
	{
		if (node->cmd_node->unused_pipe_fd == -1)
			write(2, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (node->cmd_node->cmd_table[i + 1] != NULL)
	{
		write(2, "Minishell: exit: too many arguments\n", 36);
		return ;
	}
	if (ft_isnumber(node->cmd_node->cmd_table[i]) == false)
	{
		write(2, "Minishell: exit: numeric argument required\n", 48);
		exit(255);
	}
	if (node->cmd_node->unused_pipe_fd == -1)
		write(2, "exit\n", 5);
	exit(ft_atoi(node->cmd_node->cmd_table[i]));
}
