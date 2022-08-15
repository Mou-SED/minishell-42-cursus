/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:27:44 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/15 16:52:40 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    *get_variable(t_env *m_env, char *str)
{
    
    while (m_env != NULL)
    {
        if (ft_strcmp(m_env->variable, str) == 0)
            return (ft_strdup(m_env->value));
        m_env = m_env->next;
    }
    return (ft_strdup(""));
}

bool    is_flag(char *str, int *j)
{
    int i;

    i = 0;
    if (str[i++] == '-')
    {
        while (str[i] != '\0' && str[i] == 'n')
            i++;
        if (str[i] == '\0')
        {
            *j = 1;
            return (true);
        }
    }
    return (false); 
}
void    execute_echo(t_ast *node)
{
    int     i;
    int     j;
    char    *arg;

    i = 1;
    j = 0;
    if (node->cmd_node->files != NULL)
        if (redirections(node) == false)
            return ;
    while (node->cmd_node->cmd_table[i] != NULL)
    {
        if (is_flag(node->cmd_node->cmd_table[i], &j) == false)
            break ;
        else
            i++;
    }
    while (node->cmd_node->cmd_table[i] != NULL)
    {
        arg = node->cmd_node->cmd_table[i++];
        write(node->cmd_node->fdout, arg, ft_strlen(arg));
        if (node->cmd_node->cmd_table[i] != NULL)
            write(node->cmd_node->fdout, " ", 1);
    }
    if (j != 1)
        write(node->cmd_node->fdout, "\n", 1);
}

void    execute_pwd(t_ast *node)
{
    char    *path_name;
    if (node->cmd_node->files != NULL)
        if (redirections(node) == false)
            return ;
    path_name = get_variable(*(node->cmd_node->m_env), "PWD");
    write(node->cmd_node->fdout, path_name, ft_strlen(path_name));
    write(node->cmd_node->fdout, "\n", 1);
    free(path_name);
}

void    execute_exit(t_ast *node, int sto)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (node->cmd_node->files != NULL)
        if (redirections(node) == false)
            return ;
    if (node->cmd_node->cmd_table[i] == NULL)
    {
        write(sto, "exit\n", 5);
        exit(EXIT_SUCCESS);
    }
    if (node->cmd_node->cmd_table[i + 1] != NULL)
    {
        write(sto, "Minishell: exit: too many arguments\n", 36);
        return ;
    }
    if (ft_isnumber(node->cmd_node->cmd_table[i]) == false)
    {
        write(1, "exit\nMinishell: exit: numeric argument required\n", 48);
        exit(255);
    }
    write(sto, "exit\n", 5);
    exit(ft_atoi(node->cmd_node->cmd_table[i]));
}