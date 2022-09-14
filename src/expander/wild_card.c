/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:49:40 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/12 02:29:30 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_check_to_find(char **file_name, char *to_find, char c)
{
	char	*find;

	find = NULL;
	while (true)
	{
		find = ft_strstr(*file_name, to_find);
		if (find == NULL)
			return (false);
		*file_name = find + ft_strlen(to_find);
		if (ft_strlen(find) != ft_strlen(to_find) && c == '*')
			return (true);
		else if (ft_strlen(find) == ft_strlen(to_find))
			return (true);
	}
}

char	*create_to_find(char *str, int *i, int start)
{
	int		len;
	char	*to_find;

	len = 0;
	while (str[*i] != '\0' && str[*i] != '*')
	{
		*i = *i + 1;
		len++;
	}
	to_find = ft_calloc(len + 1, sizeof(char));
	ft_memcpy(to_find, &str[start], len);
	return (to_find);
}

int	wild_card(char *str, char *file_name)
{
	int		i;
	char	*to_find;

	i = 0;
	i = skip_wildcard(str, i);
	while (str[i] != '\0')
	{
		i = skip_wildcard(str, i);
		if (str[i] == '\0')
			break ;
		if (i == 0 && str[i] != file_name[0])
			return (0);
		to_find = create_to_find(str, &i, i);
		if (ft_check_to_find(&file_name, to_find, str[i]) == false)
			return (free(to_find), 0);
		free(to_find);
	}
	return (1);
}

int	expande_wild_card(t_ast *node, char *str)
{
	char			*file_name;
	DIR				*dp;
	struct dirent	*dirp;
	int				file_exist;

	file_exist = 0;
	dp = opendir(".");
	if (dp == NULL)
		return (file_exist);
	while (1337)
	{
		dirp = readdir(dp);
		if (dirp == NULL)
			break ;
		file_name = dirp->d_name;
		if (skip_dir(file_name) != 1
			&& wild_card(str, file_name) != 0)
		{
			file_exist = 1;
			add_argument(node, file_name);
		}
	}
	return (closedir(dp), file_exist);
}
