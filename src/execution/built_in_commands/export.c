/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:40:25 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/24 10:53:42 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	exist_var(char *str, t_env *m_env)
{
	int		i;
	char	*var_name;

	i = var_name_len(str);
	var_name = ft_calloc((i + 1), sizeof(char));
	ft_memcpy(var_name, str, i);
	while (m_env)
	{
		if (ft_strcmp(var_name, m_env->variable) == 0)
		{
			if (str[i] == '\0')
				return (free(var_name), true);
			else
			{
				update_value(m_env, str, i);
				return (free(var_name), true);
			}
		}
		m_env = m_env->next;
	}
	return (free(var_name), false);
}

void	export_varible(char *str, t_env **m_env)
{
	int		i;
	t_env	*new_var;

	new_var = ft_calloc(1, sizeof(t_env));
	i = 0;
	i = var_name_len(str);
	new_var->variable = ft_calloc((i + 1), sizeof(char));
	ft_memcpy(new_var->variable, str, i);
	new_var->variable[i] = '\0';
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
	{
		new_var->value = NULL;
		new_var->export_history = true;
		new_var->exported_to_env = false;
	}
	else
	{
		new_var->value = ft_strdup(&str[++i]);
		new_var->export_history = true;
		new_var->exported_to_env = true;
	}
	add_variable(m_env, new_var);
}

void	execute_export(t_ast *node)
{
	int	i;

	i = 1;
	dup2(node->cmd_node->fdout, 1);
	if (!node->cmd_node->cmd_table[i])
	{
		display_export(*node->cmd_node->m_env);
		return_normal_mode(*node->cmd_node->m_env);
	}
	else
		run_export(node);
	if (g_status != 1)
		g_status = 0;
}

void	update_value(t_env *m_env, char *str, int i)
{
	if (str[i++] == '+')
		m_env->value = add_value(m_env->value, &str[++i]);
	else
	{
		if (m_env->value)
			free(m_env->value);
		m_env->value = ft_strdup(&str[i]);
	}
	m_env->export_history = true;
	m_env->exported_to_env = true;
}

void	run_export(t_ast *node)
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
			if (exist_var(node->cmd_node->cmd_table[i],
					*(node->cmd_node->m_env)) == false)
				export_varible(node->cmd_node->cmd_table[i],
					node->cmd_node->m_env);
		}
		i++;
	}
}
