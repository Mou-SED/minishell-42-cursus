/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mode_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:27:36 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 23:28:21 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	check_state_quote(int *state, char c)
{
	if (*state == 1)
		*state = 0;
	if (c == '"' || c == '\'')
	{
		if (*state == 1)
			*state = 0;
		if (*state == c)
			*state = 0;
		else if (*state == 0)
			*state = c;
	}
}
