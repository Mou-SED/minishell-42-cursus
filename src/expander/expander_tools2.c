/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:20:35 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/10 15:41:11 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_variable_as_argument(t_ast *node,
			char *var_value, char **update_str)
{
	char	**splited_value;
	int		index;

	index = 0;
	splited_value = ft_split(var_value, ' ');
	if (splited_value == NULL)
	{
		if (*update_str == NULL)
			*update_str = ft_strdup("");
	}
	else
	{
		if (*update_str != NULL)
			splited_value[0] = ft_strjoin(*update_str, splited_value[0]);
		while (splited_value[index + 1] != NULL)
		{
			add_argument(node, splited_value[index]);
			free(splited_value[index++]);
		}
		free (*update_str);
		*update_str = splited_value[index];
		free(splited_value);
	}
}

char	*expande_variable_herdoc(char **update_str, char *str, t_env *m_env)
{
	int		i;
	char	*var_value;
	char	*var_name;

	i = 0;
	i = skip_dollars(str);
	if (str[i] == '?')
	{
		if (str[++i] != '\0' && str[i] != '$')
			i++;
		var_value = ft_itoa(g_status);
	}
	else
	{
		while (str[i] != '\0' && str[i] != '"' && str[i] != '\''
			&& str[i] != '$' && str[i] != ' ' && is_not_special_char(str[i]))
			i++;
		var_name = ft_substr(str, 0, i);
		var_value = get_variable(m_env, var_name);
		free(var_name);
	}
	if (var_value != NULL)
		*update_str = join_expended_str(*update_str, var_value);
	return (free(var_value), (str + i) - 1);
}
