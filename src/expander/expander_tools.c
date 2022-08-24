/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:42:15 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/24 10:42:38 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
