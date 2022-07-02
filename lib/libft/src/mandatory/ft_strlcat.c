/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:14:55 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:02:06 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (dst[i] != '\0')
	{
		i++;
	}
	k = 0;
	while (src[k] != '\0')
		k++;
	if (len <= i)
		k = k + len;
	else
		k = k + i;
	j = 0;
	while (src[j] != '\0' && i + 1 < len)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (k);
}
