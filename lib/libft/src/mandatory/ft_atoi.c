/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:32:56 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:00:53 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		r;
	char	*ptr;

	ptr = (char *)str;
	i = 0;
	s = 1;
	r = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == 32)
		i++;
	while ((ptr[i] == '-') || (str[i] == '+'))
	{
		if (ptr[i] == '-')
			s = s * -1;
		if (ptr[i + 1] == '-' || ptr[i + 1] == '+')
			return (0);
		i++;
	}
	while ((ptr[i] >= '0') && (ptr[i] <= '9'))
	{
		r = (r * 10) + (ptr[i] - '0');
		i++;
	}
	return (r * s);
}
