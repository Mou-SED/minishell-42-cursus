#ifndef EXECUTION_H
#define EXECUTION_H
# include <minishell.h>

// pipe 
void    create_pipe(t_ast *pipe_node);

// execute cmd
void    execution(t_ast *root);
void    execute_cmd(t_ast *node);


// errors functions
void	execution_errors(char *str);

// files
bool    check_file(char *filename, t_r mode);
bool    redirections(t_ast *node);

// Helpful Functions
void    get_cmd(t_ast *node);

//Built in
void    echo_cmd(char **arg);
#endif