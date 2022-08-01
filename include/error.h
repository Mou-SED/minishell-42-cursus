/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:05:39 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/01 14:45:48 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include "syntax_analysis.h"

void	ft_print_error(char *str);
bool	check_syntax_error(t_token_list *node);
bool	check_empty_parenthesis(t_ast *root);
bool	her_doc(t_token_list *token);

#endif