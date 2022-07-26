/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:12 by zaabou            #+#    #+#             */
/*   Updated: 2022/07/26 01:12:10 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYSIS_H
# define SYNTAX_ANALYSIS_H
# include "minishell.h"


typedef enum e_node
{
    AND,
    OR,
    CMD,
    PIP,
    PAR
}   t_node;

typedef  struct s_cmd
{
    char    **cmd_table;
    char    *cmd_args;
    char    *out_files;
    char    *in_files;
    int     fdin;
    int     fdout;
}   t_cmd;

typedef  struct s_pipe
{
    int pipe_fd[2];
}   t_pipe;


typedef struct s_ast
{
    t_node          type;
    struct s_ast    *right;
    struct s_ast    *left;
    t_cmd           *cmd_node;
    t_pipe          *pipe_node;
}   t_ast;


#endif