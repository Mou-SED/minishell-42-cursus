/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:53:27 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/22 14:51:10 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool    check_if_built_in(t_ast *node)
{
    int     i;
    char    **cmd_name;

    cmd_name = ft_split(node->cmd_node->cmd_args, ' ');
    if (cmd_name == NULL)
        return (false);
    i = 0;
    if (!ft_strcmp("echo", cmd_name[0]) || !ft_strcmp("ECHO", cmd_name[0])
        || !ft_strcmp("unset", cmd_name[0]) || !ft_strcmp("cd", cmd_name[0])
            || !ft_strcmp("export", cmd_name[0]) || !ft_strcmp("env", cmd_name[0])
                || !ft_strcmp("ENV", cmd_name[0]) || !ft_strcmp("exit", cmd_name[0])
                    || !ft_strcmp("pwd", cmd_name[0]) || !ft_strcmp("PWD", cmd_name[0]))
        {
            while (cmd_name[i])
                free(cmd_name[i++]);
            free(cmd_name);
            return (true);
        }
    while (cmd_name[i])
        free(cmd_name[i++]);
    free(cmd_name);
    return (false);
}

void    execute_built_in(t_ast *node, char **cwd)
{
    int stdo;
    int stin;

    if (node->cmd_node->unused_pipe_fd != -1)
        close(node->cmd_node->unused_pipe_fd);
    stdo = dup(1);
    stin = dup(0);
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "echo") || !ft_strcmp(node->cmd_node->cmd_table[0], "ECHO"))
        execute_echo(node);
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "PWD") || !ft_strcmp(node->cmd_node->cmd_table[0], "pwd"))
        execute_pwd(node, &(*cwd));
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "exit"))
        execute_exit(node);
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "unset"))
        execute_unset(node);
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "env") || !ft_strcmp(node->cmd_node->cmd_table[0], "ENV"))
        execute_env(node);
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "export"))
        execute_export(node);
    if (!ft_strcmp(node->cmd_node->cmd_table[0], "cd"))
        execute_cd(node, &(*cwd));
    close(node->cmd_node->fdin);
    close(node->cmd_node->fdout);
    dup2(stdo, 1);
    dup2(stin, 0);
}