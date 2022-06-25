/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_lstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:18:42 by moseddik          #+#    #+#             */
/*   Updated: 2022/03/01 20:43:57 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_d_lstadd_front(t_d_list **alst, t_d_list *new)
{
	if (!alst && !*alst)
		return ;
	new->next = *alst;
    (*alst)->prev = new;
    *alst = new;
}
