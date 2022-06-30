/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:34:03 by zaabou            #+#    #+#             */
/*   Updated: 2022/06/30 12:41:16 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLER_H
# define SIG_HANDLER_H

# include <signal.h>
# include <termios.h>

void	signals_handler(void);
void	ctl_d_handler(char *cmd);

#endif
