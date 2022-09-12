/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:20:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/09 20:48:43 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	build_env(t_env *m_env, char **env)
{
	if (env[0] != NULL)
		duplicate_env(m_env, env);
	else
		create_env(m_env, "SHLVL", "1");
	add_var_not_exist(m_env);
}

void	create_env(t_env *m_env, char *var_name, char *var_value)
{
	m_env->variable = ft_strdup(var_name);
	m_env->value = ft_strdup(var_value);
	m_env->exported_to_env = true;
	if (ft_strcmp(var_name, "_") == 0)
		m_env->export_history = false;
	else
		m_env->export_history = true;
	if (ft_strcmp(m_env->variable, "SHLVL") == 0)
	{
		m_env->next = ft_calloc(1, sizeof(t_env));
		create_env(m_env->next, "_", "/usr/bin/env");
	}
}

void	duplicate_env(t_env *m_env, char **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;
	int		j;

	i = -1;
	tmp = m_env;
	while (env[++i])
	{
		tmp->exported_to_env = true;
		tmp->export_history = true;
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp->variable = ft_calloc((j + 1), sizeof(char));
		ft_memcpy(tmp->variable, env[i], j);
		duplicate_env_2(tmp, env, i, j);
		if (env[i + 1] != NULL)
			tmp->next = ft_calloc(1, sizeof(t_env));
		prev = tmp;
		tmp = tmp->next;
		if (tmp)
			tmp->prev = prev;
	}
}

char	**convert_envirenment(t_env *m_env)
{
	t_env	*tmp;
	char	**env;
	int		i;

	i = 0;
	env = NULL;
	if (m_env == NULL)
		return (env);
	tmp = m_env;
	while (tmp)
	{
		if (tmp->exported_to_env == true)
			i++;
		tmp = tmp->next;
	}
	env = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (m_env)
	{
		if (m_env->exported_to_env == true)
				env[i++] = ft_strjoin_char(m_env->variable, m_env->value, '=');
		m_env = m_env->next;
	}
	env[i] = NULL;
	return (env);
}

void	remove_env(t_env **m_env)
{
	t_env	*tmp;

	while (*m_env)
	{
		tmp = *m_env;
		*m_env = (*m_env)->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	free(m_env);
}
