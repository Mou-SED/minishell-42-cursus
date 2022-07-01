/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/01 17:29:14 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int ac, char **av)
{
	char	*cmd;

	(void)ac;
	(void)av;
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		ctl_d_handler(cmd);
	}
}
