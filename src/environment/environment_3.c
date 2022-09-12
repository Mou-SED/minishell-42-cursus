/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:41:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/09 21:49:15 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	var_not_exist(t_env *m_env, char *var_name)
{
	while (m_env)
	{
		if (ft_strcmp(m_env->variable, var_name) == 0)
			return (true);
		m_env = m_env->next;
	}
	return (false);
}

void	duplicate_env_2(t_env *tmp, char **env, int i, int j)
{
	if (ft_strcmp(tmp->variable, "OLDPWD") == 0)
	{
		tmp->export_history = true;
		tmp->exported_to_env = false;
	}
	if (ft_strcmp(tmp->variable, "_") == 0)
		tmp->export_history = false;
	if (ft_strcmp(tmp->variable, "SHLVL") == 0)
	{
		if (ft_atoi(&env[i][j + 1]) < 0)
			tmp->value = ft_itoa(0);
		else
			tmp->value = ft_itoa(ft_atoi(&env[i][j + 1]) + 1);
	}
	if (ft_strcmp(tmp->variable, "PWD") == 0)
		tmp->value = ft_get_cwd();
	else if (ft_strcmp(tmp->variable, "SHLVL")
		&& ft_strcmp(tmp->variable, "OLDPWD")
		&& ft_strcmp(tmp->variable, "PWD"))
		tmp->value = ft_strdup(&env[i][j + 1]);
}

void	add_var_not_exist(t_env *m_env)
{
	if (var_not_exist(m_env, "PWD") == false)
		creat_and_add_var(m_env, "PWD");
	if (var_not_exist(m_env, "OLDPWD") == false)
		creat_and_add_var(m_env, "OLDPWD");
	if (var_not_exist(m_env, "PATH") == false)
		creat_and_add_var(m_env, "PATH");
	if (var_not_exist(m_env, "SHLVL") == false)
		creat_and_add_var(m_env, "SHLVL");
}

void	creat_and_add_var(t_env *m_env, char *var_name)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	node->variable = ft_strdup(var_name);
	if (ft_strcmp(var_name, "PWD") == 0)
		node->value = ft_get_cwd();
	if (ft_strcmp(var_name, "OLDPWD") == 0)
	{
		node->export_history = true;
		node->exported_to_env = false;
	}
	if (ft_strcmp(var_name, "PATH") == 0)
	{
		node->value = ft_strdup(_PATH_STDPATH);
		node->export_history = false;
		node->exported_to_env = false;
	}
	if (ft_strcmp(var_name, "SHLVL") == 0)
		node->value = ft_itoa(1);
	if (!ft_strcmp(var_name, "SHLVL") || !ft_strcmp(var_name, "PWD"))
	{
		node->export_history = true;
		node->exported_to_env = true;
	}
	add_variable(&m_env, node);
}
