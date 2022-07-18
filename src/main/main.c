/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/18 16:37:28 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_tokens(t_token_list *head)
{
	char	*str[7] = {"WORD", "PIPE", "REDIRECTION", "OPERATOR",
		"LEFTPAREN", "RIGHTPAREN"};
	if (head == NULL)
		printf("head is Null\n");
	while (head != NULL)
	{
		printf("[%s] --> [%s]\n", head->lexeme, str[head->type]);
		head = head->next;
	}
}

int	main(int ac, char **av)
{
	char			*cmd;
	t_token_list	**head;
	char			*cmd_trim;

	(void)ac;
	(void)av;
	head = ft_calloc(1, sizeof(t_token_list *));
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		if (cmd != NULL && *cmd != 0)
		{
			cmd_trim = ft_strtrim(cmd, " ");
			*head = ft_lstnew_token("content");
			(add_history(cmd), tokenizer(cmd_trim, head));
			(free(cmd), free(cmd_trim));
			(ft_print_tokens(*head), ft_lstclear_token(head, &free));
		}
		else if (cmd == NULL)
			ctl_d_handler();
	}
}
