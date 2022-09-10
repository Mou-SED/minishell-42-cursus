/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:42:15 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 15:59:38 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_not_special_char(char c)
{
	if (c != '~' && c != '`' && c != '!'&& c != '@'
		&& c != '#' && c != '$'
		&& c != '%' && c != '^' && c != '&'
		&& c != '*' && c != '-' && c != '+'
		&& c != '=' && c != '{' && c != '}'
		&& c != '[' && c != ']' && c != '/'
		&& c != ':' && c != ';' && c != ','
		&& c != '.')
		return (true);
	return (false);
}

char	*join_expended_str(char *s1, char *s2)
{
	char	*new_str;
	int		len;

	if (!s1 && s2)
		return (ft_strdup(s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = ft_calloc(len + 1, sizeof(char));
	ft_memcpy(new_str, s1, ft_strlen(s1));
	ft_memcpy(new_str + ft_strlen(s1), s2, ft_strlen(s2));
	new_str[len] = '\0';
	free(s1);
	return (new_str);
}

int	skip_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '$')
	{
		if (str[i] == '$' && str[i + 1] != '$')
			break ;
		i++;
	}
	return (i);
}

char	**get_arguments(char ***table)
{
	char	**new_table;

	new_table = NULL;
	new_table = *table;
	*table = NULL;
	return (new_table);
}

void	add_argument(t_ast *node, char *new_arg)
{
	char	**new_table;
	int		index;

	if (node->cmd_node->cmd_table == NULL)
	{
		node->cmd_node->cmd_table = ft_calloc(2, sizeof(char *));
		node->cmd_node->cmd_table[0] = ft_strdup(new_arg);
		return ;
	}
	index = 0;
	while (node->cmd_node->cmd_table[index])
		index++;
	new_table = ft_calloc(index + 2, sizeof(char *));
	index = 0;
	while (node->cmd_node->cmd_table[index])
	{
		new_table[index] = ft_strdup(node->cmd_node->cmd_table[index]);
		free(node->cmd_node->cmd_table[index]);
		node->cmd_node->cmd_table[index++] = NULL;
	}
	new_table[index] = ft_strdup(new_arg);
	free(node->cmd_node->cmd_table);
	node->cmd_node->cmd_table = new_table;
}
