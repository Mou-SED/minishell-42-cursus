/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:57:13 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/17 00:00:18 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_env *m_env)
{
	while (m_env)
	{
		printf("%s=%s\n", m_env->variable, m_env->value);
		m_env = m_env->next;
	}
}

void	execute_env(t_ast *node)
{
	if (node->cmd_node->files != NULL)
	{
		if (redirections(node) == false)
		{
			status = 1;
			return ;
		}
	}
	print_env(*(node->cmd_node->m_env));
	status = 0;
}
