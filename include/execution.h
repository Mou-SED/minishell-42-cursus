/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:27:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/27 15:51:14 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <minishell.h>

# define PCDE "\x1b[31m cd: error retrieving current directory:\
getcwd: cannot access parent directories: %s\x1b[0m\n"

// pipe
void	create_pipe(t_ast *pipe_node);

// execute cmd
void	execution(t_ast *node, char **cwd);
void	execute_cmd(t_ast *node, char **cwd);
void	exec_cmd(t_ast *node);
void	*subshell(t_ast *root, char **cwd);
void	run_child(t_ast *node, char **cwd, int error_files);

// errors functions
void	execution_errors(char *str);

// files
bool	check_file(char *filename, t_r mode);
bool	redirections(t_ast *node);
void	unused_pipe(t_ast *node);
bool	out_files(t_ast *node, t_lst *tmp);
bool	in_files(t_ast *node, t_lst *tmp);
void	expande_files_name(char **filename, t_env *m_env);


// Helpful Functions
int		open_files(t_ast *node);
char	*get_cmd(t_ast *node);
void	failed_fork(void);

//Built in
bool	check_if_built_in(t_ast *node);
void	execute_built_in(t_ast *node, char **cwd, int error_files);
void	check_more_built_in(t_ast *node, char **cwd);
void	execute_echo(t_ast *node);
void	execute_pwd(t_ast *node, char **cwd);
void	execute_exit(t_ast *node);
void	execute_cd(t_ast *node, char **cwd);
void	execute_unset(t_ast *node);
void	execute_env(t_ast *node);
void	print_env(t_env *m_env);
void	execute_export(t_ast *node);
void	export_varible(char *str, t_env **m_env);

// export tools
void	run_export(t_ast *node);
char	*add_value(char *str1, char *str2);
int		var_name_len(char *str);
void	return_normal_mode(t_env *m_env);
void	print_element(t_env *m_env);
bool	check_valid_name(char *str);
void	display_export(t_env *m_env);
void	update_value(t_env *m_env, char *str, int i);

// tools
bool	ft_isnumber(char *str);
char	*join_path(char *cwd, char *arg);
int		go_to_old_dir(t_ast *node);
void	update_cwd_help(char **cwd, char *folderpath,
			t_env *oldpwd, t_env *pwd);

#endif