/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:50:56 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/27 19:05:28 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_variable(t_env **m_env, t_env *var)
{
	t_env	*tmp;

	tmp = *m_env;
	if (tmp == NULL)
		tmp = var;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = var;
		var->prev = tmp;
	}
}

char	*get_variable(t_env *m_env, char *var)
{
	while (m_env != NULL)
	{
		if (ft_strcmp(m_env->variable, var) == 0)
		{
			if (m_env->value == NULL)
				return (NULL);
			else
				return (ft_strdup(m_env->value));
		}
		m_env = m_env->next;
	}
	return (NULL);
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
			free(tmp->variable);
			free(tmp->value);
			free(tmp);
			return ;
		}
		else
			node = node->next;
	}
}

t_env	*get_access_to_var(t_env *m_env, char *variable)
{
	while (m_env)
	{
		if (!ft_strcmp(m_env->variable, variable))
			return (m_env);
		m_env = m_env->next;
	}
	return (NULL);
}
