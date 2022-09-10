/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 04:11:18 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 16:30:48 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_update_str(char **str, char c)
{
	int		len;
	char	*new_str;

	if (*str == NULL)
	{
		*str = ft_calloc(2, sizeof(char));
		**str = c;
		return ;
	}
	new_str = NULL;
	len = (int)ft_strlen(*str);
	new_str = ft_calloc(len + 2, sizeof(char));
	ft_memcpy(new_str, *str, len);
	new_str[len++] = c;
	new_str[len] = '\0';
	free(*str);
	*str = new_str;
	return ;
}

char	*single_quote_case(char **update_str, char *str)
{
	if (*str == '\0' || *str == '\'' )
	{
		if (*update_str == NULL)
			*update_str = ft_strdup("");
		return (str);
	}
	else
		ft_update_str(&(*update_str), *str);
	return (single_quote_case(&(*update_str), ++str));
}

char	*expande_variable(t_ast *node, char **update_str, char *str, t_env *m_env, int state)
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
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i] != '?'
			&& is_not_special_char(str[i]))
			i++;
		var_name = ft_substr(str, 0, i);
		var_value = get_variable(m_env, var_name);
		free(var_name);
	}
	if (var_value != NULL)
	{
		if (state == 0)
			add_variable_as_argument(node, var_value, &(*update_str));
		else
			*update_str = join_expended_str(*update_str, var_value);
	}
	return (free(var_value), (str + i) - 1);
}

void	expande_str(t_ast *node, char **update_str, char *str, int state, t_env *m_env)
{
	if (*str == '\0')
		return ;
	if (*str == '$' && *(str + 1) != '\0'
		&& is_not_special_char(*(str + 1)))
		str = expande_variable(node, &(*update_str), ++str, m_env, state);
	else if (*str == '\'' && state == 0)
		str = single_quote_case(&(*update_str), ++str);
	else if (*str != '"')
		ft_update_str(&(*update_str), *str);
	if (*str == '"')
	{
		if (state == 0)
		{
			if (*update_str == NULL)
				*update_str = ft_strdup("");
			state = 1;
		}
		else
			state = 0;
	}
	expande_str(node, &(*update_str), ++str, state, m_env);
}

void	expander(t_ast *node, int index, char **cp_of_arguments)
{
	char	*new_arg;

	new_arg = NULL;
	if (cp_of_arguments[index] == NULL)
	{
		free_table(cp_of_arguments);
		return ;
	}
	expande_str(node, &new_arg,
		cp_of_arguments[index++], 0, *(node->cmd_node->m_env));
	if (new_arg != NULL)
		add_argument(node, new_arg);
	free(new_arg);
	expander(node, index, cp_of_arguments);
}
