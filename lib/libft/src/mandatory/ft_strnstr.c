/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:57:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:02:25 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	char	*find;

	ptr = (char *)str;
	find = (char *)to_find;
	i = 0;
	if (find[0] == '\0')
		return (ptr);
	else if (find[0] == '\0' && ptr[0] == '\0')
		return (0);
	while (ptr[i] != '\0')
	{
		j = 0;
		while (ptr[i + j] == find[j] && (j + i) < len)
		{
			if (find[j + 1] == '\0')
				return (&ptr[i]);
			j++;
		}
		i++;
	}
	return (0);
}
