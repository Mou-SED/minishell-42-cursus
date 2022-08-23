/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:45:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 14:36:14 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_path(char *cwd, char *arg)
{
	int		i;
	int		j;
	int		len;
	char	*new_path;

	i = 0;
	j = 0;
	len = ft_strlen(cwd) + ft_strlen(cwd);
	new_path = ft_calloc(len + 2, sizeof(char));
	if (new_path == NULL)
		allocation_faild();
	while (cwd[i])
		new_path[j++] = cwd[i++];
	new_path[j++] = '/';
	i = 0;
	while (arg[i])
		new_path[j++] = arg[i++];
	new_path[j] = '\0';
	return (free(cwd), new_path);
}
