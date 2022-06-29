/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:34:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/06/29 21:48:59 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SIG_HANDLER_H
# define SIG_HANDLER_H

# include <signal.h>

void    scan_input(int sig);
void	ctl_c_handle();
void	ctl_d_handler(char *cmd);
void	ctl_backslash_handle(void);
void	handel_signals(void);
# endif
