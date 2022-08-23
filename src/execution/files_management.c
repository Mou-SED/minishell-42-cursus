/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:53:14 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 22:53:34 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	out_files(t_ast *node)
{
	if (node->cmd_node->fdout != 1)
		close(node->cmd_node->fdout);
	if (access(node->cmd_node->files->filename, F_OK) != 0)
		node->cmd_node->fdout
			= open(node->cmd_node->files->filename, O_CREAT | O_WRONLY,
				0644);
	else if (check_file(node->cmd_node->files->filename, W_TRUNC)
		== false)
		return (false);
	else if (node->cmd_node->files->mode == W_APPRND)
		node->cmd_node->fdout
			= open(node->cmd_node->files->filename,
				O_WRONLY | O_APPEND);
	else if (node->cmd_node->files->mode == W_TRUNC)
		node->cmd_node->fdout
			= open(node->cmd_node->files->filename,
				O_WRONLY | O_TRUNC);
	return (true);
}

bool	in_files(t_ast *node)
{
	if (node->cmd_node->fdin)
		close(node->cmd_node->fdin);
	if (check_file(node->cmd_node->files->filename, READ) == false)
		return (false);
	node->cmd_node->fdin
		= open(node->cmd_node->files->filename, O_RDONLY);
	return (true);
}
