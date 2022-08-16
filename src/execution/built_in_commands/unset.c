/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:26:22 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/16 23:59:22 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_unset(t_ast *node)
{
	int	i;

	i = 1;
	if (node->cmd_node->files != NULL)
	{
		if (redirections(node) == false)
		{
			status = 1;
			return ;
		}
	}
	while (node->cmd_node->cmd_table[i])
		remove_variable(node->cmd_node->m_env, node->cmd_node->cmd_table[i++]);
	status = 0;
}
