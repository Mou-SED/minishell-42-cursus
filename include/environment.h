/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:43:55 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/15 16:03:28 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef	struct env
{
	char		*variable;
	char		*value;
	struct env	*next;
}t_env;

// functions
void    add_variable(t_env **m_env, t_env *var);
char	*get_variable(t_env *m_env, char *str);
#endif