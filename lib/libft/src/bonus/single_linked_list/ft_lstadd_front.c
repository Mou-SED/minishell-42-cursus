/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:35:18 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:03:18 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst && !*alst)
		return ;
	new->next = *alst;
	*alst = new;
}
