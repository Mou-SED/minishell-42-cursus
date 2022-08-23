/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:30:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 22:55:25 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>

char	*get_cmd(t_ast *node)
{
	int		i;
	char	*path;
	char	*absolute_path;

	if (ft_strchr(node->cmd_node->cmd_table[0], '/') != NULL)
		return (ft_strdup(node->cmd_node->cmd_table[0]));
	i = 0;
	path = get_variable(*(node->cmd_node->m_env), "PATH");
	if (path == NULL)
		(printf("Minishell: %s: No such file or directory\n",
				node->cmd_node->cmd_table[0]), exit(127));
	node->cmd_node->paths = ft_split(path, ':');
	if (node->cmd_node->paths == NULL)
		allocation_faild();
	free(path);
	while (node->cmd_node->paths[i])
	{
		absolute_path = ft_strjoin_char(node->cmd_node->paths[i],
				node->cmd_node->cmd_table[0], '/');
		if (absolute_path && access(absolute_path, X_OK) == 0)
			break ;
		free(absolute_path);
		i++;
	}
	return (absolute_path);
}

bool	redirections(t_ast *node)
{
	while (node->cmd_node->files)
	{
		if (node->cmd_node->files->mode == W_APPRND
			|| node->cmd_node->files->mode == W_TRUNC)
		{
			if (out_files(node) == false)
				return (false);
		}
		else if (node->cmd_node->files->mode == READ)
		{
			if (in_files(node) == false)
				return (false);
		}
		node->cmd_node->files = node->cmd_node->files->next;
	}
	return (true);
}

bool	check_file(char *filename, t_r mode)
{
	if (mode == W_TRUNC)
	{
		if (access(filename, W_OK) != 0)
		{
			execution_errors(filename);
			return (false);
		}
	}
	else if (mode == READ)
	{
		if (access(filename, R_OK) != 0)
		{
			execution_errors(filename);
			return (false);
		}
	}
	return (true);
}

void	failed_fork(void)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("Minishell : Error : %s\n", strerror(errno));
}
