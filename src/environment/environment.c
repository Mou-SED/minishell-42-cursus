/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:20:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/17 00:05:47 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_own_env(t_env **m_env, char **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;
	int		j;

	i = -1;
	tmp = ft_calloc(1, sizeof(t_env));
	*m_env = tmp;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp->variable = ft_calloc((j + 1), sizeof(char));
		ft_memcpy(tmp->variable, env[i], j);
		if (ft_strcmp(tmp->variable, "SHLVL") == 0)
			tmp->value = ft_itoa(ft_atoi(&env[i][j + 1]) + 1);
		if (ft_strcmp(tmp->variable, "SHELL") == 0)
			tmp->value = ft_strdup("minishell");
		else if (ft_strcmp(tmp->variable, "SHLVL")
			&& ft_strcmp(tmp->variable, "SHELL"))
			tmp->value = ft_strdup(&env[i][j + 1]);
		if (env[i] && env[i + 1])
			tmp->next = ft_calloc(1, sizeof(t_env));
		prev = tmp;
		tmp = tmp->next;
		if (tmp)
			tmp->prev = prev;
	}
}

void	add_variable(t_env **m_env, t_env *var)
{
	t_env	*tmp;

	tmp = *m_env;
	if (tmp == NULL)
		tmp = var;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = var;
}

char	*get_variable(t_env *m_env, char *var)
{
	while (m_env != NULL)
	{
		if (ft_strcmp(m_env->variable, var) == 0)
			return (ft_strdup(m_env->value));
		m_env = m_env->next;
	}
	return (ft_strdup(""));
}

void	remove_variable(t_env **m_env, char *var)
{
	t_env	*tmp;
	t_env	*node;

	node = *m_env;
	while (node)
	{
		if (ft_strcmp(node->variable, var) == 0)
		{
			if (*m_env == node)
				*m_env = node->next;
			if (node && node->prev != NULL)
				node->prev->next = node->next;
			if (node && node->next != NULL)
				node->next->prev = node->prev;
			tmp = node;
			node = node->next;
			free(tmp->variable);
			free(tmp->value);
			free(tmp);
		}
		else
			node = node->next;
	}
}
