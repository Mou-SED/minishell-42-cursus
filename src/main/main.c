/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/06 17:01:23 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_tokens(t_token_list *head)
{
	t_token_list  *tmp;
	if (head == NULL)
		printf("head is Null\n");
	while (head != NULL)
	{
		printf("--> [%s]\n", head->lexeme);
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}

int	main(int ac, char **av)
{
	char			*cmd;
	t_token_list	**head;

	(void)ac;
	(void)av;

	head = malloc(sizeof(t_token_list *));
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		if (cmd != NULL && *cmd != 0)
		{
			(add_history(cmd), tokenizer(cmd, head));
			ft_print_tokens(*head);
			*head = ft_lstnew_token("content");
		}
		else if (cmd == NULL)
			ctl_d_handler();
	}
}
