/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:08:44 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/11 16:30:55 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_add_string_to_table(char ***table, char *new_string)
{
	char	**new_table;
	int		index;

	if (*table == NULL)
	{
		(*table) = ft_calloc(2, sizeof(char *));
		(*table)[0] = ft_strdup(new_string);
		return ;
	}
	index = 0;
	while ((*table)[index])
		index++;
	new_table = ft_calloc(index + 2, sizeof(char *));
	index = 0;
	while ((*table)[index])
	{
		new_table[index] = ft_strdup((*table)[index]);
		free((*table)[index]);
		(*table)[index++] = NULL;
	}
	new_table[index] = ft_strdup(new_string);
	free(*table);
	*table = new_table;
}

char	*get_arg(char *begin, char *end)
{
	char	*new_str;
	char	*save_begin;
	int		index;

	save_begin = begin;
	index = 0;
	while (begin != end)
	{
		begin++;
		index++;
	}
	new_str = ft_calloc(index + 1, sizeof(char));
	ft_memcpy(new_str, save_begin, index);
	return (new_str);
}

char	*next_c(char *str, char c)
{
	char	quote_type;

	if (*str == '\0' || *str == c)
		return (str);
	else if (*str == '\'' || *str == '"')
	{
		quote_type = *str;
		str++;
		while (*str != '\0' && *str != quote_type)
			str++;
	}
	return (next_c(++str, c));
}

void	creat_table(char ***table, char *str, char c)
{
	char	*begin;
	char	*arg;

	if (*str == '\0')
		return ;
	str = skip_space(str);
	if (*str == '\0')
		return ;
	begin = str;
	str = next_c(str, c);
	arg = get_arg(begin, str);
	ft_add_string_to_table(&(*table), arg);
	free(arg);
	creat_table(&(*table), str, c);
}

char	**ft_split_mode(char *str, char c)
{
	char	**table;

	table = NULL;
	return (creat_table(&table, str, c), table);
}
