/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:04:41 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 14:44:53 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_pwd(t_ast *node, char **cwd)
{
	if (node->cmd_node->files != NULL)
	{
		if (redirections(node) == false)
		{
			status = 1;
			return ;
		}
	}
	printf("%s\n", *cwd);
}
