/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:03:06 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/21 00:17:29 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_error(char *str)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("MiniShell: syntax error near unexpected token `%s'\n", str);
}

void	execution_errors(char *str)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("\x1b[33m Minishell : %s: %s\x1b[0m\n", str, strerror(errno));
}

void	allocation_faild(void)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("MiniShell: Error: %s\n", strerror(errno));
	exit(12);
}
