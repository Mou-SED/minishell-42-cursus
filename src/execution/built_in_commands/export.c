/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:40:25 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 14:44:40 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_value(char *str1, char *str2)
{
	int		i;
	int		j;
	int		len;
	char	*new_value;

	if (str1 == NULL)
		return (ft_strdup(str2));
	len = ft_strlen(str1) + ft_strlen(str2);
	new_value = ft_calloc(len + 1, sizeof(char));
	if (new_value == NULL)
		allocation_faild();
	i = 0;
	j = 0;
	while (str1[j])
		new_value[i++] = str1[j++];
	j = 0;
	while (str2[j])
		new_value[i++] = str2[j++];
	new_value[i] = '\0';
	return (free(str1), new_value);
}

int	var_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		else
			i++;
	}
	return (i);
}

void	return_normal_mode(t_env *m_env)
{
	if (m_env == NULL)
		return ;
	m_env->is_printed = false;
	return_normal_mode(m_env->next);
}

void	print_element(t_env *m_env)
{
	if (m_env->export_history == true)
	{
		printf("declare -x %s", m_env->variable);
		if (m_env->value != NULL)
			printf("=\"%s\"", m_env->value);
		printf("\n");
	}
	m_env->is_printed = true;
}

void	display_export(t_env *m_env)
{
	t_env	*tmp;
	t_env	*smaller;

	while (m_env)
	{
		if (m_env->is_printed == false)
		{
			tmp = m_env;
			smaller = m_env;
			while (tmp)
			{
				if (tmp->is_printed == false)
				{
					if (ft_strcmp(tmp->variable, smaller->variable) <= 0)
						smaller = tmp;
				}
				tmp = tmp->next;
			}
			print_element(smaller);
		}
		else
			m_env = m_env->next;
	}
	return ;
}

bool	exist_var(char *str, t_env *m_env)
{
	int		i;
	char	*var_name;

	i = 0;
	i = var_name_len(str);
	var_name = malloc((i + 1) * sizeof(char));
	ft_memcpy(var_name, str, i);
	var_name[i] = '\0';
	while (m_env)
	{
		if (ft_strcmp(var_name, m_env->variable) == 0)
		{
			if (str[i] == '\0')
				return (free(var_name), true);
			else
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
				return (free(var_name), true);
			}
		}
		m_env = m_env->next;
	}
	free(var_name);
	return (false);
}

void	export_varible(char *str, t_env **m_env)
{
	int		i;
	t_env	*new_var;

	new_var = ft_calloc(1, sizeof(t_env));
	i = 0;
	i = var_name_len(str);
	new_var->variable = malloc((i + 1) * sizeof(char));
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

bool	check_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		if (str[i] == ' ' || (!ft_isalnum(str[i]) && str[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}

void    execute_export(t_ast *node)
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
	dup2(node->cmd_node->fdout, 1);
	if (!node->cmd_node->cmd_table[i])
	{
		display_export(*node->cmd_node->m_env);
		return_normal_mode(*node->cmd_node->m_env);
	}
	else
	{
		while (node->cmd_node->cmd_table[i])
		{
			if (check_valid_name(node->cmd_node->cmd_table[i]) == false)
			{
				write(2, "Minishell: export: unvalid identifier\n", 38);
				status = 1;
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
	if (status != 1)
		status = 0;
}
