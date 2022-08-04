#ifndef EXECUTION_H
#define EXECUTION_H
# include <minishell.h>

void    get_cmd(t_ast *node);
void    execute_cmd(t_ast *node);
void    execution(t_ast *root);
void    create_pipe(t_ast *pipe_node);
#endif