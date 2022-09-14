/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:46:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/11 18:50:29 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <paths.h>
# include "../lib/libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <environment.h>
# include <sig_handler.h>
# include <token.h>
# include <heredoc.h>
# include <error.h>
# include <syntax_analysis.h>
# include <expander.h>
# include <execution.h>

bool	tokenization(char *cmd, t_token_list ***head, t_env *m_env);
void	waiting_for_my_children(void);
void	wait_for_one_child(pid_t pid);
void	create_own_env(t_env **m_env, char **env);
int		g_status;

#endif
