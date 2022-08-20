/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 23:32:00 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/21 00:28:58 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    execute_cd(t_ast *node)
{
    int i;

    i = 1;
    if (node->cmd_node->files != NULL)
    {
        if (redirections(node) == false)
        {
            status = 1;
            return ;
        }
    }
    if (chdir(node->cmd_node->cmd_table[i]) == -1)
    {
        dup2(STDERR_FILENO, STDOUT_FILENO);
        printf("\x1b[31m Minishell: cd: %s: %s\x1b[0m\n", node->cmd_node->cmd_table[i], strerror(errno));
        status = 1;
        return ;
    }
    
}