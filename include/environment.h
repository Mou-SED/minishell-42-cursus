/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:43:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/20 13:23:36 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef	struct env
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
void	create_env(t_env **m_env, char *variable, char *value);
void    add_variable(t_env **m_env, t_env *var);
char	*get_variable(t_env *m_env, char *var);
void    remove_variable(t_env **m_env, char *var);
char	**convert_envirenment(t_env *m_env);
#endif