/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:16 by moseddik          #+#    #+#             */
/*   Updated: 2021/11/21 20:22:28 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char s, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s;
	char	*st;
	char	*strtrim;

	st = (char *)set;
	s = (char *)s1;
	i = 0;
	j = ft_strlen(s);
	while (s && isset(s[i], st))
		i++;
	while (s && isset(s[j - 1], st))
		j--;
	strtrim = ft_substr(s, i, (j - i));
	return (strtrim);
}
