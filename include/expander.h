/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:40 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/06 11:48:20 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <minishell.h>

// expander functions
void	expander(t_ast *node, int index, char **cp_of_arguments);
void	expande_str(char **update_str, char *str, int state, t_env *m_env);
char	*single_quote_case(char **update_str, char *str);
void	ft_update_str(char **str, char c);
char	*expande_variable(char **update_str, char *str, t_env *m_env);
void	add_argument(t_ast *node, char *new_arg);
char	**cp_arguments(char ***table);

// Expander tools
char	*join_expended_str(char *s1, char *s2);
int		skip_dollars(char *str);
bool	is_not_special_char(char c);
#endif
