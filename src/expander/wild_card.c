/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:49:40 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/11 19:15:31 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

int	skip_dir(char *dir)
{
	if (ft_strcmp(dir, ".") == 0 || ft_strcmp(dir, "..") == 0)
		return (1);
	return (0);
}

int skip_wildcard(char *str, int i)
{
	while (str[i] == '*')
		i++;
	return (i);
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
	to_find = calloc(len + 1, sizeof(char));
	ft_memcpy(to_find, &str[start], len);
	return (to_find);
}

int	wild_card(char *str, char *file_name)
{
	int 	i;
	char	*to_find;
	char	*find;

	i = 0;
	while (str[i] != '\0')
	{
		i = skip_wildcard(str, i);
		if (i == 0 && str[i] != file_name[0])
			return (0);
		to_find = create_to_find(str, &i, i);
		find = ft_strstr(file_name, to_find);
		file_name = find;
		if (find == NULL)
			return (free(to_find), 0);
		if (ft_strncmp(to_find, find, ft_strlen(to_find)) == 0)
		{
			if ((ft_strlen(find) - ft_strlen(to_find) != 0) && str[i] == '\0'
				&& str[i - 1] != '*')
				return (free(to_find), 0);
		}
		free(to_find);
	}
	return (1);
}

int	expande_wild_card(t_ast *node, char *str)
{
	char			*file_name;
    DIR 			*dp;
    struct dirent 	*dirp;
	int				file_exist;

	file_exist = 0;
    if ((dp = opendir(".")) == NULL)
	{
		if (errno == EACCES)
			printf("Permission denied\n");
		return (file_exist);
	}
    while ((dirp = readdir(dp)) != NULL)
	{
		file_name = dirp->d_name;
		if (skip_dir(file_name) == 1)
			continue ;
		if (wild_card(str, file_name) != 0)
		{
			file_exist = 1;
			add_argument(node, file_name);
		}
	}
    if (closedir(dp) == -1)
        perror("closedir");
	return (file_exist);
}
