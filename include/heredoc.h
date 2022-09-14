/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:41:58 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 19:46:41 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include <minishell.h>

bool	run_herdoc(t_token_list *token, t_env *m_env);
void	herdoc_child(char *filename, t_token_list *token, t_env *m_env);

// heredoc tools
void	expande_helper(char **herdoc, char *str, t_env *m_env);
void	expende_dollar(char **herdoc, t_env *m_env);
void	expande(char **delemeter, char *old_delemeter, int state);
void	expand_delemeter(char **delemeter, int *state);
char	*open_random_file(char *str);

#endif