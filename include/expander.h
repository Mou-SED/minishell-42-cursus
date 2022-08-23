/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:35:40 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/22 14:40:39 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <minishell.h>

void	expander(t_ast *node, int i);

// Expander tools
char	*join_expended_str(char *s1, char *s2);
#endif