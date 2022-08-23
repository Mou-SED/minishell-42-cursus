/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:39:17 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 20:40:10 by moseddik         ###   ########.fr       */
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
