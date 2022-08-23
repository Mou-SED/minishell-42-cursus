/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:46:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 10:50:59 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <paths.h>
# include "../lib/libft/include/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include <environment.h>
# include "sig_handler.h"
# include "token.h"
# include "error.h"
# include "syntax_analysis.h"
# include <expander.h>
# include <execution.h>

void    waiting_for_my_children(void);
void    wait_for_one_child(pid_t pid);
void	create_own_env(t_env **m_env, char **env);
int 	status;

#endif
