/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:45:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 23:12:14 by moseddik         ###   ########.fr       */
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

int	go_to_old_dir(t_ast *node)
{
	char	*old_dir;

	old_dir = NULL;
	old_dir = get_variable(*node->cmd_node->m_env, "OLDPWD");
	if (old_dir == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("\x1b[31m Minishell: cd: OLDPWD not set\x1b[0m\n");
		g_status = 1;
		return (1);
	}
	else if (chdir(old_dir) == -1)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("\x1b[31m Minishell: cd: %s: %s\x1b[0m\n",
			old_dir, strerror(errno));
		g_status = 1;
	}
	else
		printf("%s\n", old_dir);
	free(old_dir);
	return (0);
}

void	update_cwd_help(char **cwd, char *folderpath, t_env *oldpwd, t_env *pwd)
{
	free(oldpwd->value);
	if (pwd->value != NULL)
		oldpwd->value = ft_strdup(pwd->value);
	else
		oldpwd->value = NULL;
	(free(pwd->value), free(*cwd));
	*cwd = folderpath;
	pwd->value = ft_strdup(*cwd);
}
