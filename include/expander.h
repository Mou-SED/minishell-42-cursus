/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:40 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 21:53:46 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <minishell.h>

void	expander(t_ast *node, int i);
void	expande_str(char **update_str, char *str, int state, t_env *m_env);
char	*single_quote_case(char **update_str, char *str);
void	ft_update_str(char **str, char c);
char	*expande_variable(char **update_str, char *str, t_env *m_env);

// Expander tools
char	*join_expended_str(char *s1, char *s2);
int		skip_dollars(char *str);
#endif