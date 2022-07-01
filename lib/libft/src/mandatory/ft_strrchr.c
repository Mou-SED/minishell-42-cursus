/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:13:52 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:02:28 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	int				j;
	char			*ptr;
	unsigned char	ch;

	ptr = (char *)str;
	ch = (unsigned char)c;
	i = 0;
	j = ft_strlen(str);
	while (j >= 0)
	{
		if (ptr[j] == ch)
		{
			return (&ptr[j]);
		}
		j--;
	}
	return (0);
}
