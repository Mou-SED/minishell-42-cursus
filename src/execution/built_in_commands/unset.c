/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:26:22 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 21:18:11 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_value(t_env *m_env, char *variable)
{
	while (m_env)
	{
		if (!ft_strcmp(m_env->variable, variable))
		{
			m_env->export_history = false;
			m_env->exported_to_env = false;
			free(m_env->value);
			m_env->value = NULL;
		}
		m_env = m_env->next;
	}
}

void	execute_unset(t_ast *node)
{
	int	i;

	i = 1;
	while (node->cmd_node->cmd_table[i])
	{
		if (check_valid_name(node->cmd_node->cmd_table[i]) == false)
		{
			write(2, "Minishell: export: unvalid identifier\n", 38);
			g_status = 1;
		}
		else
		{
			if (!ft_strcmp(node->cmd_node->cmd_table[i], "OLDPWD")
				|| !ft_strcmp(node->cmd_node->cmd_table[i], "PWD"))
				remove_value(*node->cmd_node->m_env,
					node->cmd_node->cmd_table[i]);
			else
				remove_variable(node->cmd_node->m_env,
					node->cmd_node->cmd_table[i]);
		}
		i++;
	}
	if (g_status != 1)
		g_status = 0;
}
