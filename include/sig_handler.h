/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:34:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/06 12:18:02 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H

# include "minishell.h"
# include "token.h"

void	signals_handler(void);
void	ctl_d_handler(t_token_list **head, t_env **m_env, char *cwd);
void	ctl_c_handler(void);

#endif
