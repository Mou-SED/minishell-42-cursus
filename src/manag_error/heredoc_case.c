/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:41:52 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/11 20:59:56 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"
# include <sig_handler.h>

char	*open_random_file(char *str)
{
	static	int	i;
	char	*herdoc_number;
	char	*filename;
	herdoc_number = ft_itoa(i++);
	filename = ft_strjoin(str, herdoc_number);
	filename = ft_strjoin("/tmp/minishell/", filename);
	return (filename);
}

static bool	run_herdoc(t_token_list *token)
{
	char	*heredoc;
	char	*filename;
	int fd;
	
	filename = open_random_file(token->lexeme);
	if (!fork())
	{
		signal(SIGINT, SIG_DFL);
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
				write(fd, heredoc, ft_strlen(heredoc));
				write(fd, "\n", 1);
			}
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = WTERMSIG(status);
			return (false);
		}
		free(token->lexeme);
		token->lexeme = filename;
	}
	return (true);
}

bool	her_doc(t_token_list *token)
{
	if (token->type != WORD && token->type != REDIRECTION
		&& token->type != LEFTPAREN)
		return (true);
	while (token != NULL)
	{
		if (token->next && ft_strcmp(token->lexeme, "<<") == 0)
		{
			if (run_herdoc(token->next) == false)
				return (true);
		}
		else if (token->next && (token->type == OPERATOR || token->type == PIPE)
		&& (token->next->type != WORD && token->next->type != LEFTPAREN
			&& token->next->type != REDIRECTION))
			return (true);
		else if (token->next && !ft_strcmp(token->lexeme, "(") && !ft_strcmp(token->next->lexeme, ")"))
			return (true);
		else if (token->type == REDIRECTION && token->next == NULL)
			return (ft_print_error("newline"), true);
		else if (token->next && token->type == REDIRECTION
		&& token->next->type != WORD)
			return (true); 
		else if ((token->type != WORD && token->type != RIGHTPAREN
			&& token->type != REDIRECTION) && token->next == NULL)
			return (true);
		token = token->next;
	}
	return (false);
}
