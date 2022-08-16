/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:30:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/16 23:14:58 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
void    get_cmd(t_ast *node)
{
    char    *path;
    int     i;
    char    *absolute_path;

    i = 0;
    absolute_path = NULL;
    path = get_variable(*(node->cmd_node->m_env), "PATH");
    if (path[0] == '\0')
    {
        printf("Minishell: %s: No such file or directory\n",node->cmd_node->cmd_table[0]);
        exit(127);
    }
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

bool    redirections(t_ast *node)
{
    while (node->cmd_node->files)
    {
        if (node->cmd_node->files->mode == W_APPRND || node->cmd_node->files->mode == W_TRUNC)
        {
            close(node->cmd_node->fdout);
            if (access(node->cmd_node->files->filename, F_OK) != 0)
                node->cmd_node->fdout = open(node->cmd_node->files->filename, O_CREAT | O_WRONLY ,0644);
            else if (check_file(node->cmd_node->files->filename, W_TRUNC) == false)
                    return (false);
            else if (node->cmd_node->files->mode == W_APPRND)
                node->cmd_node->fdout = open(node->cmd_node->files->filename, O_WRONLY |  O_APPEND);
            else if (node->cmd_node->files->mode == W_TRUNC)
                node->cmd_node->fdout = open(node->cmd_node->files->filename, O_WRONLY |  O_TRUNC);
        }
        else if (node->cmd_node->files->mode == READ)
        {
            close(node->cmd_node->fdin);
            if (check_file(node->cmd_node->files->filename, READ) == false)
                return (false);
            node->cmd_node->fdin = open(node->cmd_node->files->filename, O_RDONLY);
        }
        node->cmd_node->files = node->cmd_node->files->next;
    }
    return (true);
}

bool    check_file(char *filename, t_r mode)
{
    if (mode == W_TRUNC)
    {
        if (access(filename, W_OK) != 0)
        {
            execution_errors(filename);
            return (false);
        }
    }
    else if(mode == READ)
    {
        if (access(filename, R_OK) != 0)
        {
            execution_errors(filename);
            return (false);
        }
    }
    return (true);
}