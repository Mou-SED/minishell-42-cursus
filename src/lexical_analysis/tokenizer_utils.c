/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:54:39 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/08 11:56:10 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skip_space(char *str)
{
	while (*str != '\0' && *str == ' ')
		str++;
	return (str);
}

int	is_token(char *str)
{
	if (*str == '|' || *str == '>' || *str == '<'
		|| (*str == '&' && *(str + 1) == '&') || *str == '(' || *str == ')')
		return (1);
	return (0);
}
