/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 23:58:11 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:03:51 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

void	ft_d_lstdelone(t_d_list *lst, void (*del) (void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
