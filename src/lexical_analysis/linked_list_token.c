/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:48:40 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/08 11:49:12 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_list	*ft_lstnew_token(char *content)
{
	t_token_list	*head;

	head = malloc(sizeof(t_token_list));
	if (!head)
		return (NULL);
	head->lexeme = content;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_token_back(t_token_list **alst, t_token_list *new)
{
	t_token_list	*ptr;

	if (alst == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		ptr = *alst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->next = NULL;
	}
}
