/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:46:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/11 23:08:54 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../lib/libft/include/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "sig_handler.h"
# include "token.h"
# include "error.h"
# include "syntax_analysis.h"
# include <execution.h>

void    waiting_for_my_children(void);
void    wait_for_one_child(void);
int status;

#endif
