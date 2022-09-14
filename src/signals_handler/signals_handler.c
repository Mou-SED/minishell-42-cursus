/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:20:52 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/14 10:59:56 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_ctl_c(int arg)
{
	(void)arg;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

void	ctl_c_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &handle_ctl_c);
}

static void	ctl_backslash_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	ctl_d_handler(t_token_list **head, t_env **m_env, char *cwd)
{
	free(head);
	free(cwd);
	remove_env(m_env);
	rl_clear_history();
	printf("exit\n");
	exit(g_status);
}

void	signals_handler(void)
{
	ctl_backslash_handler();
	ctl_c_handler();
}
