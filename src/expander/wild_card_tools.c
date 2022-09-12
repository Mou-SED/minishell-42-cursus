/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 01:52:47 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/12 01:52:51 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_dir(char *dir)
{
	if (ft_strcmp(dir, ".") == 0 || ft_strcmp(dir, "..") == 0)
		return (1);
	return (0);
}

int	skip_wildcard(char *str, int i)
{
	while (str[i] == '*')
		i++;
	return (i);
}
