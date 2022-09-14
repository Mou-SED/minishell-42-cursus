/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 04:11:18 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/14 10:41:33 by zaabou           ###   ########.fr       */
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

char	*expande_variable(t_ast *node, char **update_str, char *str,
			t_env *m_env)
{
	int		i;
	char	*var_value;

	i = 0;
	var_value = NULL;
	if (ft_isdigit(str[i]))
		return (str);
	if (str[i] == '?')
	{
		i++;
		var_value = ft_itoa(g_status);
	}
	else
		var_value = get_variable_value(str, m_env, &i);
	if (var_value != NULL)
	{
		if (node->cmd_node->state == 0)
			add_variable_as_argument(node, var_value, &(*update_str));
		else
			*update_str = join_expended_str(*update_str, var_value);
	}
	return (free(var_value), (str + i) - 1);
}

void	expande_str(t_ast *node, char **update_str, char *str, t_env *m_env)
{
	if (*str == '\0')
		return ;
	if (*str == '$' && *(str + 1) != '\0'
		&& is_not_special_char(*(str + 1)))
		str = expande_variable(node, &(*update_str), ++str, m_env);
	else if (*str == '\'' && node->cmd_node->state == 0)
		str = single_quote_case(&(*update_str), ++str);
	else if (*str != '"')
		ft_update_str(&(*update_str), *str);
	if (*str == '"')
	{
		if (node->cmd_node->state == 0)
		{
			if (*update_str == NULL)
				*update_str = ft_strdup("");
			node->cmd_node->state = 1;
		}
		else
			node->cmd_node->state = 0;
	}
	expande_str(node, &(*update_str), ++str, m_env);
}

void	expander(t_ast *node, int index, char **cp_of_arguments)
{
	char	*new_arg;
	int		wild_card;

	new_arg = NULL;
	wild_card = 0;
	if (cp_of_arguments[index] == NULL)
	{
		free_table(cp_of_arguments);
		return ;
	}
	expande_str(node, &new_arg,
		cp_of_arguments[index++], *(node->cmd_node->m_env));
	if (new_arg != NULL)
	{
		if (ft_strchr(new_arg, '*') != NULL)
			wild_card = expande_wild_card(node, new_arg);
		if (wild_card == 0)
			add_argument(node, new_arg);
	}
	free(new_arg);
	expander(node, index, cp_of_arguments);
}
