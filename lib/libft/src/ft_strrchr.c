/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:13:52 by moseddik          #+#    #+#             */
/*   Updated: 2021/11/21 17:53:21 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
