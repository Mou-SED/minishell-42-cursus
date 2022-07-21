/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:12 by zaabou            #+#    #+#             */
/*   Updated: 2022/07/21 16:18:56 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYSIS_H
# define SYNTAX_ANALYSIS_H
# include "minishell.h"

typedef  struct s_cmd
{
    char    *string;
    char    **cmd;
    int     fdin;
    int     fdout;
}   t_cmd;

typedef  struct s_pipe
{
    int pipe_fd[2];
}   t_pipe;


typedef struct s_ast
{
    t_token_type    type;
    struct s_ast    *right;
    struct s_ast    *left;
    t_cmd           *cmd_node;
    t_pipe          *pipe_node;
}   t_ast;


#endif