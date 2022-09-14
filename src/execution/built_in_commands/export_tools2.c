/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:43:05 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 20:44:01 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
