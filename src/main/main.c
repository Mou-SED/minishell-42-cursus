/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/06/26 20:07:24 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *cmd;

	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002 ");
		if (cmd == NULL)
		{
			printf("exit\n");
			break ;
		}
	}
}
