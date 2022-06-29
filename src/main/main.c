/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/06/29 21:48:04 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_d_handler(char *cmd)
{
	if (cmd == NULL)
	{
		printf("\x1B[1;A\x1B[11;Cexit\n");
		exit(EXIT_SUCCESS);
	}
}

void	ctl_backslash_handle(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	handel_signals(void)
{
	ctl_backslash_handle();
}

int	main(int ac, char **av)
{
	char	*cmd;

	(void)ac;
	(void)av;
	handel_signals();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		ctl_d_handler(cmd);
	}
}
