/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:46:17 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/11 18:47:27 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strstr(const char *str, const char *to_find)
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
		while (ptr[i + j] == find[j])
		{
			if (find[j + 1] == '\0')
				return (&ptr[i]);
			j++;
		}
		i++;
	}
	return (0);
}
