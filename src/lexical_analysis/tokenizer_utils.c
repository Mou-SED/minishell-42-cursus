/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:54:39 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/13 10:59:26 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skip_space(char *str)
{
	while (*str != '\0' && (*str == ' ' || *str == '\t'))
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
