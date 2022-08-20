/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:02:05 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/21 00:26:09 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_flag(char *str, int *j)
{
	int	i;

	i = 0;
	if (str[i++] == '-')
	{
		while (str[i] != '\0' && str[i] == 'n')
			i++;
		if (str[i] == '\0')
		{
			*j = 1;
			return (true);
		}
	}
	return (false);
}

void	execute_echo(t_ast *node)
{
	int		i;
	int		j;
	char	*arg;

	i = 1;
	j = 0;
	if (node->cmd_node->files != NULL)
		if (redirections(node) == false)
		{
			status = 1;
			return ;
		}
	while (node->cmd_node->cmd_table[i] != NULL)
	{
		if (is_flag(node->cmd_node->cmd_table[i], &j) == false)
			break ;
		else
			i++;
	}
	while (node->cmd_node->cmd_table[i] != NULL)
	{
		arg = node->cmd_node->cmd_table[i];
		if (arg != NULL)
			write(node->cmd_node->fdout, arg, ft_strlen(arg));
		if (node->cmd_node->cmd_table[i] != NULL)
			write(node->cmd_node->fdout, " ", 1);
		i++;
	}
	if (j != 1)
		write(node->cmd_node->fdout, "\n", 1);
}
