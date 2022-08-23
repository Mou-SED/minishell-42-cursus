/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:02:05 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/23 21:14:13 by moseddik         ###   ########.fr       */
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

void	print_args(t_ast *node, int i)
{
	char	*arg;

	while (node->cmd_node->cmd_table[i] != NULL)
	{
		arg = node->cmd_node->cmd_table[i];
		if (arg != NULL)
			write(node->cmd_node->fdout, arg, ft_strlen(arg));
		if (node->cmd_node->cmd_table[i + 1] != NULL)
			write(node->cmd_node->fdout, " ", 1);
		i++;
	}
}

void	execute_echo(t_ast *node)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (node->cmd_node->cmd_table[i] != NULL)
	{
		if (is_flag(node->cmd_node->cmd_table[i], &j) == false)
			break ;
		else
			i++;
	}
	print_args(node, i);
	if (j != 1)
		write(node->cmd_node->fdout, "\n", 1);
	g_status = 0;
}
