/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:04:41 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/16 23:57:58 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pwd(t_ast *node)
{
	char	*path_name;

	if (node->cmd_node->files != NULL)
	{
		if (redirections(node) == false)
		{
			status = 1;
			return ;
		}
	}
	path_name = getcwd(NULL, 0);
	write(node->cmd_node->fdout, path_name, ft_strlen(path_name));
	write(node->cmd_node->fdout, "\n", 1);
	free(path_name);
}
