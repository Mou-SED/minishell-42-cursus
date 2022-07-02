/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:01:34 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:04:00 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

t_d_list	*ft_d_lstnew(void *content)
{
	t_d_list	*head;

	head = malloc(sizeof(t_d_list));
	if (!head)
		return (NULL);
	head->prev = NULL;
	head->content = content;
	head->next = NULL;
	return (head);
}
