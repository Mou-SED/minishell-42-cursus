/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:20:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/21 00:22:32 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <paths.h>
void	build_env(t_env *m_env, char **env)
{
	char	*str;

	if (env[0] != NULL)
		duplicate_env(m_env, env);
	else
	{
		str = getcwd(NULL, 0);
		if (str == NULL)
		{
			printf("Minishell : ERROR : %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		m_env->variable = ft_strdup("OLDPWD");
		m_env->export_history = true;
		m_env->exported_to_env = false;
		m_env->next = ft_calloc(1, sizeof(t_env));
		create_env(&m_env->next, "PWD", str);
	}
}

void	create_env(t_env **m_env, char *variable, char *value)
{		
	(*m_env)->variable = ft_strdup(variable);
	if (ft_strcmp((*m_env)->variable, "PWD") == 0)
		(*m_env)->value = value;
	else
		(*m_env)->value = ft_strdup(value);
	if (ft_strcmp(variable, "PATH") != 0)
	{
		if (ft_strcmp(variable, "_") == 0)
			(*m_env)->export_history = false;
		else
			(*m_env)->export_history = true;
		(*m_env)->exported_to_env = true;
		(*m_env)->next = ft_calloc(1, sizeof(t_env));
	}
	else
	{
		(*m_env)->export_history = false;
		(*m_env)->exported_to_env = false;
	}
	if (ft_strcmp((*m_env)->variable, "PWD") == 0)
		create_env(&(*m_env)->next, "SHELVL", "1");
	if (ft_strcmp((*m_env)->variable, "SHELVL") == 0)
		create_env(&(*m_env)->next, "_", "/usr/bin/env");
	if (ft_strcmp((*m_env)->variable, "_") == 0)
		create_env(&(*m_env)->next, "PATH", _PATH_STDPATH);

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
		if (ft_strcmp(tmp->variable, "_") == 0)
			tmp->export_history = false;
		if (ft_strcmp(tmp->variable, "SHLVL") == 0)
			tmp->value = ft_itoa(ft_atoi(&env[i][j + 1]) + 1);
		else if (ft_strcmp(tmp->variable, "SHLVL")
				&& ft_strcmp(tmp->variable, "OLDPWD"))
			tmp->value = ft_strdup(&env[i][j + 1]);
		if (ft_strcmp(tmp->variable, "OLDPWD") == 0)
			tmp->exported_to_env = false;
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
	var->prev = tmp;
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
			node = node->next;
			free(tmp->variable);
			free(tmp->value);
			free(tmp);
		}
		else
			node = node->next;
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
	env = malloc((i + 1) * sizeof(char *));
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