/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:03:06 by zaabou            #+#    #+#             */
/*   Updated: 2022/07/22 14:56:07 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_error(char *str)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("MiniShell: syntax error near unexpected token `%s'\n", str);
}
