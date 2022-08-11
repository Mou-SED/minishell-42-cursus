/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:29:49 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/11 23:26:22 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void    *subshell(t_ast *root)
{
    if (!fork())
    {
        if (root->cmd_node->unused_pipe_fd != -1)
            close(root->cmd_node->unused_pipe_fd);
        root->cmd_node->cmd_table = ft_split(root->cmd_node->cmd_args, ' ');
        if (root->cmd_node->files != NULL)
            if (redirections(root) == false)
                exit(EXIT_FAILURE);
        dup2(root->cmd_node->fdin, 0);
        dup2(root->cmd_node->fdout, 1);
        execution(root->right);
        waiting_for_my_children();
        exit(0);
    }
    else 
    {
        if (root->cmd_node->fdin != 0)
			close(root->cmd_node->fdin);
		if (root->cmd_node->fdout != 1)
			close(root->cmd_node->fdout);
    }
    return (NULL);
}
void    execute_cmd(t_ast *node)
{
    if (!fork())
    {
        if (node->cmd_node->unused_pipe_fd != -1)
            close(node->cmd_node->unused_pipe_fd);
        node->cmd_node->cmd_table = ft_split(node->cmd_node->cmd_args, ' ');
        if (node->cmd_node->files != NULL)
            if (redirections(node) == false)
                exit(EXIT_FAILURE);
        if (!node->cmd_node->cmd_table)
            exit(EXIT_FAILURE);
        else
            get_cmd(node);
        dup2(node->cmd_node->fdout, 1);
        dup2(node->cmd_node->fdin, 0);
        execve(node->cmd_node->cmd_args, node->cmd_node->cmd_table, NULL);
        dup2(STDERR_FILENO, STDOUT_FILENO);
        printf("\x1b[32m Minshell : %s: command not found\n\x1b[0m", node->cmd_node->cmd_table[0]);
        exit(127);
    }
    else
    {
        if (node->cmd_node->fdin != 0)
			close(node->cmd_node->fdin);
		if (node->cmd_node->fdout != 1)
			close(node->cmd_node->fdout);
        
    }
}

void    create_pipe(t_ast *pipe_node)
{
    int fd[2];

    pipe(fd);
    if (pipe_node->cmd_node->fdin != 0 && pipe_node->left && pipe_node->left->cmd_node)
        pipe_node->left->cmd_node->fdin = pipe_node->cmd_node->fdin;
    if (pipe_node->left && pipe_node->left->cmd_node)
    {
        pipe_node->left->cmd_node->unused_pipe_fd = fd[0];
        pipe_node->left->cmd_node->fdout = fd[1];
    }
    if (pipe_node->right && pipe_node->right->cmd_node)
    {
        pipe_node->right->cmd_node->unused_pipe_fd = fd[1];
        pipe_node->right->cmd_node->fdin = fd[0];
    }
}

void    execution(t_ast *root)
{
    if (root == NULL)
        return ;
    if (root->type == PIP)
        create_pipe(root);
    if (root->type == CMD)
        execute_cmd(root);
    else if (root->type == PAR)
        root->right = subshell(root);
    execution(root->left);
    execution(root->right);
}

