/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:05:39 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/22 15:58:59 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include "syntax_analysis.h"

void	ft_print_error(char *str);
bool	check_syntax_error(t_token_list *node, int *i);
bool	her_doc(t_token_list *token, int *i, t_env *m_env);
void	herdoc_child(char *filename, t_token_list *token, t_env *m_env);
void    allocation_faild(void);

#endif