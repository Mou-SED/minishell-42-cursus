/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:40 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 14:58:58 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <minishell.h>

// expander functions
void    expander(t_ast *node, int index, char **cp_of_arguments);
void	expande_str(t_ast *node, char **update_str, char *str, int state, t_env *m_env);
char	*single_quote_case(char **update_str, char *str);
void	ft_update_str(char **str, char c);
char	*expande_variable(t_ast *node, char **update_str, char *str, t_env *m_env, int state);
void    add_argument(t_ast *node, char *new_arg);
char	**get_arguments(char ***table);
void    expande_file(char **update_str, char *str, int state, t_env *m_env);
char	*expande_var_file_name(char **update_str, char *str, t_env *m_env);
void    add_variable_as_argument(t_ast *node, char *var_value, char **update_str);
char	*expande_variable_herdoc(char **update_str, char *str, t_env *m_env);

// Expander tools
char	*join_expended_str(char *s1, char *s2);
int		skip_dollars(char *str);
bool	is_not_special_char(char c);
#endif
