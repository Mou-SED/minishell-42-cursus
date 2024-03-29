/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:43:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/09 17:00:07 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct env
{
	char		*variable;
	char		*value;
	bool		export_history;
	bool		exported_to_env;
	bool		is_printed;
	struct env	*next;
	struct env	*prev;
}t_env;

// functions
void	build_env(t_env *m_env, char **env);
void	duplicate_env(t_env *m_env, char **env);
void	create_env(t_env *m_env, char *var_name, char *var_value);
void	add_variable(t_env **m_env, t_env *var);
char	*get_variable(t_env *m_env, char *var);
void	remove_variable(t_env **m_env, char *var);
char	**convert_envirenment(t_env *m_env);
void	remove_env(t_env **m_env);
t_env	*get_access_to_var(t_env *m_env, char *variable);
bool	path_not_exist(t_env *m_env);
void	add_path(t_env *m_env);
void	duplicate_env_2(t_env *tmp, char **env, int i, int j);
char	*ft_get_cwd(void);
void	add_var_not_exist(t_env *m_env);
void	creat_and_add_var(t_env *m_env, char *var_name);

#endif
