/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:46:59 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/03 18:59:12 by zaabou           ###   ########.fr       */
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
void	tokenizer(void);
void	parsing(void);

#endif
