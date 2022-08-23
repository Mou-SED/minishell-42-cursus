/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:08:44 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 23:38:57 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	j;
	int	state;

	i = 0;
	j = 0;
	state = 0;
	while (s[i])
	{
		check_state_quote(&state, s[i]);
		if (s[i] != c && i == 0)
		{
			i++;
			j++;
		}
		if (s[i] && s[i] == c && s[i - 1] != c && state == 0)
			j++;
		i++;
	}
	return (j);
}

static void	*free_tab(char **tab, int index)
{
	while (--index)
		free(tab[index]);
	free(tab);
	return (NULL);
}

static char	**remplis(char **splitstr, char const *s, char c, int num_of_word)
{
	t_spl_mode_var	spl;

	spl.i = 0;
	spl.k = 0;
	spl.start = 0;
	spl.state = 1;
	while (s[spl.k] && spl.i < num_of_word)
	{
		spl.items_word = 0;
		while (s[spl.k] && s[spl.k] == c)
			spl.k++;
		while (s[spl.k])
		{
			if (s[spl.k] == c && spl.state == 0)
				break ;
			check_state_quote(&spl.state, s[spl.k]);
			if (++spl.items_word == 1)
				spl.start = spl.k;
			spl.k++;
		}
		splitstr[spl.i] = ft_substr(s, spl.start, spl.items_word);
		if (!splitstr[spl.i++])
			return (free_tab(&splitstr[spl.i - 1], spl.i - 1));
	}
	return (splitstr[spl.i] = 0, splitstr);
}

char	**ft_split_mode(char const *s, char c)
{
	int		num_of_word;
	char	**splitstr;

	if (!s)
		return (NULL);
	num_of_word = count_word(s, c);
	splitstr = (char **)malloc(sizeof(char *) * (num_of_word + 1));
	if (!splitstr)
		return (0);
	return (remplis(splitstr, s, c, num_of_word));
}
