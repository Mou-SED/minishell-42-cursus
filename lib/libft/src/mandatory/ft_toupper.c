/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:39:34 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:02:41 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_toupper(int c)
{
	unsigned int	i;

	i = 0;
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	return (c);
}
