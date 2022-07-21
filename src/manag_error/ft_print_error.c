/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:03:06 by zaabou            #+#    #+#             */
/*   Updated: 2022/07/21 17:09:18 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_error(char *str)
{
	ft_putstr_fd("Error : ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}
