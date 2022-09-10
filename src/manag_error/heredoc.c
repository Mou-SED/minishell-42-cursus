/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:47:03 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 11:50:27 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	run_herdoc(t_token_list *token, t_env *m_env)
{
	char	*filename;

	filename = open_random_file(token->lexeme);
	if (!fork())
		herdoc_child(filename, token, m_env);
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&g_status);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
		{
			free(filename);
			g_status = WTERMSIG(g_status);
			return (false);
		}
		free(token->lexeme);
		token->lexeme = filename;
	}
	return (true);
}

void	herdoc_child(char *filename, t_token_list *token, t_env *m_env)
{
	char	*heredoc;
	int		fd;
	int		state;

	rl_catch_signals = 1;
	state = 0;
	(signal(SIGINT, SIG_DFL), expand_delemeter(&token->lexeme, &state));
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (1)
	{
		heredoc = readline("> ");
		if ((token && heredoc && ft_strcmp(heredoc, token->lexeme) == 0))
			break ;
		else if (heredoc == NULL)
			break ;
		else
		{
			if (state == 1 && heredoc[0] != '\0')
				expende_dollar(&heredoc, m_env);
			write(fd, heredoc, ft_strlen(heredoc));
			write(fd, "\n", 1);
		}
		free(heredoc);
	}
	exit(0);
}

void	expand_delemeter(char **delemeter, int *state)
{
	char	*old_delemeter;

	if (!ft_strchr(*delemeter, '\'') && !ft_strchr(*delemeter, '"'))
		*state = 1;
	old_delemeter = ft_strdup(*delemeter);
	free(*delemeter);
	*delemeter = NULL;
	expande(&(*delemeter), old_delemeter, 0);
	if (*delemeter == NULL)
		*delemeter = ft_strdup("");
	free(old_delemeter);
	old_delemeter = NULL;
}

char	*open_random_file(char *str)
{
	static long	i;
	char		*herdoc_number;
	char		*filename;

	herdoc_number = ft_itoa(i++);
	filename = ft_strjoin(str, herdoc_number);
	filename = ft_strjoin("/tmp/minishell/", filename);
	return (filename);
}
