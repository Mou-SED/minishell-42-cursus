/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:57:13 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 21:18:21 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_env *m_env)
{
	while (m_env)
	{
		if (m_env->exported_to_env == true)
			printf("%s=%s\n", m_env->variable, m_env->value);
		m_env = m_env->next;
	}
}

void	execute_env(t_ast *node)
{
	dup2(node->cmd_node->fdout, 1);
	print_env(*(node->cmd_node->m_env));
	g_status = 0;
}
