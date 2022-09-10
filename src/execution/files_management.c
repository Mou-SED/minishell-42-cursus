/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:53:14 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 00:40:32 by zaabou           ###   ########.fr       */
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
	else 
	{
		if (check_file(tmp->filename, W_TRUNC) == false)
			return (false);
		if (tmp->mode == W_APPRND)
			node->cmd_node->fdout = open(tmp->filename,
				O_WRONLY | O_APPEND);
		if (tmp->mode == W_TRUNC)
			node->cmd_node->fdout = open(tmp->filename,
				O_WRONLY | O_TRUNC);
	}
	if (node->cmd_node->fdout == -1)
		return (redirection_error(tmp->filename, strerror(errno)), false);
	return (true);
}

bool	in_files(t_ast *node, t_lst *tmp)
{
	if (node->cmd_node->fdin != 0)
		close(node->cmd_node->fdin);
	if (check_file(tmp->filename, READ) == false)
		return (false);
	node->cmd_node->fdin
		= open(tmp->filename, O_RDONLY);
	return (true);
}

bool	expande_files_name(char **filename, t_env *m_env)
{
	char	*old_filename;

	old_filename = ft_strdup(*filename);
	free(*filename);
	*filename = NULL;
	expande_str(&(*filename), old_filename, 0, m_env);
	if (*filename == NULL)
	{
		redirection_error(old_filename, "ambiguous redirect");
		return (free(old_filename), false);
	}
	else if (**filename == '\0')
	{
		redirection_error("", "No such file or directory");
		return (free(old_filename), false);	
	}
	return (free(old_filename), true);
}
