/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_lstmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 00:16:44 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:03:58 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

t_d_list	*ft_d_lstmap(t_d_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_d_list	*ptr;
	t_d_list	*temp;

	ptr = NULL;
	while (lst)
	{
		temp = ft_d_lstnew(f(lst->content));
		if (!temp)
		{
			ft_d_lstclear(&ptr, del);
			return (NULL);
		}
		ft_d_lstadd_back(&ptr, temp);
		lst = lst->next;
	}
	return (ptr);
}
