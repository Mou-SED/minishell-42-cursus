/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:30:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/04 13:40:51 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    get_cmd(t_ast *node)
{
    char    *path;
    int     i;
    char    *absolute_path;

    i = 0;
    absolute_path = NULL;
    path = getenv("PATH");
    if (!path)
        exit(5);
    node->cmd_node->paths = ft_split(path, ':');
    while (node->cmd_node->paths[i])
    {
        absolute_path = ft_strjoin_char(node->cmd_node->paths[i], node->cmd_node->cmd_table[0], '/');
        if (absolute_path && access(absolute_path, X_OK) == 0)
        {
            free(node->cmd_node->cmd_args);
            node->cmd_node->cmd_args = absolute_path;
            return;
        }
        free(absolute_path);
        i++;
    }
}