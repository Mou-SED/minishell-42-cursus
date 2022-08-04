/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:29:49 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/04 14:38:39 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    execute_cmd(t_ast *node)
{
    if (!fork())
    {
        node->cmd_node->cmd_table = ft_split(node->cmd_node->cmd_args, ' ');
        get_cmd(node);
        dup2(node->cmd_node->fdout, 1);
        dup2(node->cmd_node->fdin, 0);
        execve(node->cmd_node->cmd_args, node->cmd_node->cmd_table, NULL);
        printf("Command Not Found\n");
        exit(EXIT_FAILURE);
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
        pipe_node->left->cmd_node->fdout = fd[1];
    if (pipe_node->right && pipe_node->right->cmd_node)
        pipe_node->right->cmd_node->fdin = fd[0];
}

void    execution(t_ast *root)
{
    if (root == NULL)
        return ;
    if (root->type == PIP)
        create_pipe(root);
    if (root->type == CMD)
        execute_cmd(root);
    execution(root->left);
    execution(root->right);
}