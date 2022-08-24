/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:42:52 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/24 10:48:19 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include <minishell.h>

void	*ft_calloc(size_t count, size_t size)
{
	int	*ptr;

	ptr = (int *)malloc(count * size);
	if (ptr == NULL)
		allocation_faild();
	ft_bzero(ptr, count * size);
	return (ptr);
}
