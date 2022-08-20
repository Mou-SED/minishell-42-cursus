/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:26:22 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/20 19:07:03 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_value(t_env *m_env)
{
	while (m_env)
	{
		if (!ft_strcmp(m_env->variable, "OLDPWD")
			|| !ft_strcmp(m_env->variable, "PWD"))
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
	if (node->cmd_node->files != NULL)
	{
		if (redirections(node) == false)
		{
			status = 1;
			return ;
		}
	}
	while (node->cmd_node->cmd_table[i])
	{
		if (check_valid_name(node->cmd_node->cmd_table[i]) == false)
		{
			write(2, "Minishell: export: unvalid identifier\n", 38);
			status = 1;
		}
		else
		{
			if (!ft_strcmp(node->cmd_node->cmd_table[i], "OLDPWD")
				|| !ft_strcmp(node->cmd_node->cmd_table[i], "PWD"))
				remove_value(*node->cmd_node->m_env);
			else
				remove_variable(node->cmd_node->m_env, node->cmd_node->cmd_table[i]);
		}
		i++;
	}
	if (status != 1)
        status = 0;
}
