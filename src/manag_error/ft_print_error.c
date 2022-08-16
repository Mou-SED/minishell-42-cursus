/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:03:06 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/17 00:07:14 by zaabou           ###   ########.fr       */
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
	printf("\x1b[32m Minishell : %s: %s\n\x1b[0m", str, strerror(errno));
}
