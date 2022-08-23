/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 23:32:00 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 23:12:43 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_cwd(t_ast *node, char **cwd, int mode, char *folderpath)
{
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = get_access_to_var(*node->cmd_node->m_env, "OLDPWD");
	pwd = get_access_to_var(*node->cmd_node->m_env, "PWD");
	if (mode == 1)
		update_cwd_help(cwd, folderpath, oldpwd, pwd);
	else if (node->cmd_node->cmd_table[1]
		&& (!ft_strcmp(node->cmd_node->cmd_table[1], "..")
			|| !ft_strcmp(node->cmd_node->cmd_table[1], ".")))
	{
		free(oldpwd->value);
		if (pwd->value != NULL)
			oldpwd->value = ft_strdup(pwd->value);
		else
			oldpwd->value = NULL;
		*cwd = join_path(*cwd, node->cmd_node->cmd_table[1]);
		free(pwd->value);
		pwd->value = ft_strdup(*cwd);
	}
}

void	check_valid_folder(t_ast *node, char **cwd, int i)
{
	char	*folder_path;

	folder_path = getcwd(NULL, 0);
	if (folder_path == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf(PCDE, strerror(errno));
		update_cwd(node, &(*cwd), 0, NULL);
	}
	else if (i == 0)
		update_cwd(node, &(*cwd), 1, folder_path);
}

int	go_to_dir(t_ast *node)
{
	int		i;

	i = 1;
	if (ft_strcmp(node->cmd_node->cmd_table[i], "-") == 0)
	{
		if (go_to_old_dir(node) == 1)
			return (1);
	}
	else if (chdir(node->cmd_node->cmd_table[i]) == -1)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("\x1b[31m Minishell: cd: %s: %s\x1b[0m\n",
			node->cmd_node->cmd_table[i], strerror(errno));
		g_status = 1;
	}
	return (0);
}

void	go_to_home(t_ast *node)
{
	char	*home;

	home = NULL;
	home = get_variable(*node->cmd_node->m_env, "HOME");
	if (home == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("Minishell: cd: HOME not set\n");
		g_status = 1;
	}
	else if (chdir(home) == -1)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("\x1b[31m Minishell: cd: %s: %s\x1b[0m\n",
			home, strerror(errno));
		g_status = 1;
	}
	free(home);
}

void	execute_cd(t_ast *node, char **cwd)
{
	int	i;

	i = 1;
	dup2(node->cmd_node->fdout, 1);
	if (node->cmd_node->cmd_table[i] == NULL)
		go_to_home(node);
	else
		i = go_to_dir(node);
	check_valid_folder(node, &(*cwd), i);
	return ;
}
