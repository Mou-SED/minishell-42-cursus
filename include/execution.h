#ifndef EXECUTION_H
#define EXECUTION_H
# include <minishell.h>

// pipe 
void    create_pipe(t_ast *pipe_node);

// execute cmd
void    execution(t_ast *root);
void    execute_cmd(t_ast *node);
void    run_child(t_ast *node);


// errors functions
void	execution_errors(char *str);

// files
bool    check_file(char *filename, t_r mode);
bool    redirections(t_ast *node);

// Helpful Functions
char    *get_cmd(t_ast *node);
void    failed_fork();

//Built in
bool    check_if_built_in(t_ast *node);
void    execute_built_in(t_ast *node);
void    execute_echo(t_ast *node);
void    execute_pwd(t_ast *node);
void	execute_exit(t_ast *node);
void    execute_cd(t_ast *node);
void    execute_unset(t_ast *node);
void    execute_env(t_ast *node);
void    print_env(t_env *m_env);
void    execute_export(t_ast *node);
void    export_varible(char *str, t_env **m_env);


// tools
bool    ft_isnumber(char *str);
bool    check_valid_name(char *str);
#endif