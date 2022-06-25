/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 22:49:31 by moseddik          #+#    #+#             */
/*   Updated: 2021/11/21 20:21:31 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && i == 0)
		{
			i++;
			j++;
		}
		if (s[i] != c && s[i - 1] == c && s[i] != '\0')
			j++;
		i++;
	}
	return (j);
}

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	*free_tab(char **tab, int index )
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
	char	*str;

	i = 0;
	k = 0;
	start = 0;
	while (s[k] && i < num_of_word)
	{
		items_word = 0;
		while (s[k] && s[k] == c)
			k++;
		while (s[k++] && s[k - 1] != c)
			if (++items_word == 1)
				start = k - 1;
		splitstr[i] = (char *)malloc(sizeof(char) * (items_word + 1));
		if (!splitstr[i])
			return (free_tab(&splitstr[i], i));
		str = ft_substr(s, start, items_word);
		ft_strcpy(splitstr[i++], str);
		free(str);
	}
	return (splitstr[i] = 0, splitstr);
}

char	**ft_split(char const *s, char c)
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
