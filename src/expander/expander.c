/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 04:11:18 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/30 15:06:26 by moseddik         ###   ########.fr       */
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
		return (str);
	else
		ft_update_str(&(*update_str), *str);
	return (single_quote_case(&(*update_str), ++str));
}

bool	is_not_special_char(char c)
{
	if (c != '+' && c != '~' && c != '.' && c != ',' && c != '%') //TODO: Add special char
		return (true);
	return (false);
}

char	*expande_variable(char **update_str, char *str, t_env *m_env)
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

void	expande_str(char **update_str, char *str, int state, t_env *m_env)
{
	if (*str == '\0')
		return ;
	if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '\0'
		&& is_not_special_char(*(str + 1)))
		str = expande_variable(&(*update_str), ++str, m_env);
	else if (*str == '\'' && state == 0)
		str = single_quote_case(&(*update_str), ++str);
	else if (*str != '"')
		ft_update_str(&(*update_str), *str);
	if (*str == '"')
	{
		if (state == 0)
			state = 1;
		else
			state = 0;
	}
	expande_str(&(*update_str), ++str, state, m_env);
}

void	expander(t_ast *node, int i, int j, char *cp_of_string)
{
	if (cp_of_string == NULL)
		return ;
	if (i == 0)
	{
		free(node->cmd_node->cmd_table[i]);
		node->cmd_node->cmd_table[i] = NULL;
	}
	expande_str(&node->cmd_node->cmd_table[i],
		cp_of_string, 0, *(node->cmd_node->m_env));
	j++;
	free(cp_of_string);
	cp_of_string = ft_strdup(node->cmd_node->cmd_table[j]);
	free(node->cmd_node->cmd_table[j]);
	node->cmd_node->cmd_table[j] = NULL;
	if (node->cmd_node->cmd_table[i] != NULL)
		expander(node, ++i, j, cp_of_string);
	else
		expander(node, i, j, cp_of_string);
}
