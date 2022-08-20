/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:29:49 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/20 15:40:25 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void    *subshell(t_ast *root)
{
    pid_t   pid;
    pid = fork();
    if (!pid)
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
        exit(status);
    }
    else 
    {
        if (root->cmd_node->wait == true)
            wait_for_one_child(pid);
        if (root->cmd_node->fdin != 0)
			close(root->cmd_node->fdin);
		if (root->cmd_node->fdout != 1)
			close(root->cmd_node->fdout);
    }
    return (NULL);
}

void    execute_cmd(t_ast *node)
{
    pid_t   pid;

    if (check_if_built_in(node) == true && node->cmd_node->unused_pipe_fd == -1)
        execute_built_in(node);
    else
    {
        pid = fork();
        if (pid == -1)
            failed_fork();
        if (pid == 0)
        {
            if (check_if_built_in(node) == true)
                execute_built_in(node);
            else
                run_child(node);
            exit(status);
        }
        else
        {
            if (node->cmd_node->wait == true)
                wait_for_one_child(pid);
            if (node->cmd_node->fdin != 0)
	    		close(node->cmd_node->fdin);
		    if (node->cmd_node->fdout != 1)
	    		close(node->cmd_node->fdout);
        }
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
        if (pipe_node->cmd_node->wait == true)
            pipe_node->right->cmd_node->wait = true;
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
        subshell(root);
    execution(root->left);
    if ((root->type == OR && status != 0) || (root->type == AND && status == 0) || root->type == PIP)
        execution(root->right);
}

