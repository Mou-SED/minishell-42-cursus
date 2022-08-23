/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:41:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 16:27:30 by zaabou           ###   ########.fr       */
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
