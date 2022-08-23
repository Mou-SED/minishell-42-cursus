/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:41:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 23:24:06 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	path_not_exist(t_env *m_env)
{
	while (m_env)
	{
		if (ft_strcmp(m_env->variable, "PATH") == 0)
			return (true);
		m_env = m_env->next;
	}
	return (false);
}

void	add_path(t_env *m_env)
{
	t_env	*tmp;

	tmp = ft_calloc(1, sizeof(t_env));
	tmp->variable = ft_strdup("PATH");
	tmp->value = ft_calloc(30, sizeof(char));
	ft_memcpy(tmp->value, _PATH_STDPATH, 29);
	add_variable(&m_env, tmp);
}

void	duplicate_env_2(t_env *tmp, char **env, int i, int j)
{
	if (ft_strcmp(tmp->variable, "_") == 0)
		tmp->export_history = false;
	if (ft_strcmp(tmp->variable, "SHLVL") == 0)
		tmp->value = ft_itoa(ft_atoi(&env[i][j + 1]) + 1);
	else if (ft_strcmp(tmp->variable, "SHLVL")
		&& ft_strcmp(tmp->variable, "OLDPWD"))
		tmp->value = ft_strdup(&env[i][j + 1]);
	if (ft_strcmp(tmp->variable, "OLDPWD") == 0)
		tmp->exported_to_env = false;
}
