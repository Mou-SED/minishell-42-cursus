/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:08:44 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/19 00:37:14 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	check_state_quote(int *state, char c)
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
	int		i;
	int		k;
	int		start;
	int		items_word;
	int		state;
	char	*str;

	i = 0;
	k = 0;
	start = 0;
	state = 1;
	while (s[k] && i < num_of_word)
	{
		items_word = 0;
		while (s[k] && s[k] == c)
			k++;
		while (s[k])
		{
			if (s[k] == c && state == 0)
				break ;
			check_state_quote(&state, s[k]);
			if (++items_word == 1)
				start = k;
			k++;
		}
		splitstr[i] = ft_substr(s, start, items_word);
		if (!splitstr[i++])
			return (free_tab(&splitstr[i - 1], i - 1));
	}
	return (splitstr[i] = 0, splitstr);
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
