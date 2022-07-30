/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:12 by zaabou            #+#    #+#             */
/*   Updated: 2022/07/30 02:07:35 by zaabou           ###   ########.fr       */
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
    char    *redir_files;
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

// AST functions
t_ast           *ft_ast_new(t_token_list	*token);
t_ast           *building_ast(t_ast *root, t_token_list *token_list);
t_ast           *parse_operator(t_ast *root, t_token_list *token_list);
t_ast           *parse_parenteses(t_ast *node, t_token_list *token);
t_ast           *parse_cmd(t_token_list *token);
t_ast           *parse_pipe(t_ast *root, t_token_list *token);

// Memory Management functions
void            clear_ast(t_ast *root);

// Helper functions
void            join_cmd_args(t_ast *node, t_token_list *token);
t_token_list	*join_files(t_ast *node, t_token_list *token);
t_token_list    *get_next_operator(t_token_list *token_list);
t_token_list    *skip_to_right_parentheses(t_token_list *token);
char            *ft_strjoin_char(char *s1, char const *s2, char c);
#endif