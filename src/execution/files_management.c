/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:53:14 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/24 09:52:56 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	out_files(t_ast *node, t_lst *tmp)
{
	if (node->cmd_node->fdout != 1)
		close(node->cmd_node->fdout);
	if (access(tmp->filename, F_OK) != 0)
		node->cmd_node->fdout
			= open(tmp->filename, O_CREAT | O_WRONLY,
				0644);
	else if (check_file(tmp->filename, W_TRUNC)
		== false)
		return (false);
	else if (tmp->mode == W_APPRND)
		node->cmd_node->fdout
			= open(tmp->filename,
				O_WRONLY | O_APPEND);
	else if (tmp->mode == W_TRUNC)
		node->cmd_node->fdout
			= open(tmp->filename,
				O_WRONLY | O_TRUNC);
	return (true);
}

bool	in_files(t_ast *node, t_lst *tmp)
{
	if (node->cmd_node->fdin)
		close(node->cmd_node->fdin);
	if (check_file(tmp->filename, READ) == false)
		return (false);
	node->cmd_node->fdin
		= open(tmp->filename, O_RDONLY);
	return (true);
}
