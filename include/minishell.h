/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:46:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/05 21:59:52 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft/include/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "sig_handler.h"
# include "token.h"

void	scanner(void);
void	parsing(void);

#endif
