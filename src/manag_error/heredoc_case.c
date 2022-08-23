/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:41:52 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 12:54:14 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"
# include <sig_handler.h>
# include <expander.h>

void	expande_helper(char **herdoc, char *str, t_env *m_env)
{
	if (*str == '\0')
		return ;
	else if (*str == '$')
		str = expande_variable(&(*herdoc), ++str, m_env);
	else
		ft_update_str(&(*herdoc), *str);
	expande_helper(&(*herdoc), ++str, m_env);
}

void	expende_dollar(char **herdoc, t_env *m_env)
{
	char	*herdoc_cp;

	herdoc_cp = ft_strdup(*herdoc);
	free(*herdoc);
	*herdoc = NULL;
	expande_helper(&(*herdoc), herdoc_cp, m_env);
	if (*herdoc ==  NULL)
		*herdoc = ft_strdup("");
	free(herdoc_cp);
	herdoc_cp = NULL;
}

void	expande(char **delemeter, char *old_delemeter, int state)
{
	if (*old_delemeter == '\0')
		return;
	if (*old_delemeter == '\'' && state == 0)
		old_delemeter = single_quote_case(&(*delemeter), ++old_delemeter);
	else if (*old_delemeter != '"')
		ft_update_str(&(*delemeter), *old_delemeter);
	if (*old_delemeter == '"')
	{
		if (state == 0)
			state = 1;
		else
			state = 0;
	}
	expande(&(*delemeter), ++old_delemeter, state);
}

char	*open_random_file(char *str)
{
	static	long	i;
	char	*herdoc_number;
	char	*filename;
	herdoc_number = ft_itoa(i++);
	filename = ft_strjoin(str, herdoc_number);
	filename = ft_strjoin("/tmp/minishell/", filename);
	return (filename);
}

static bool	run_herdoc(t_token_list *token, t_env *m_env)
{
	char	*filename;

	filename = open_random_file(token->lexeme);
	if (!fork())
		herdoc_child(filename, token, m_env);
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			free(filename);
			status = WTERMSIG(status);
			return (false);
		}
		free(token->lexeme);
		token->lexeme = filename;
	}
	return (true);
}

bool	her_doc(t_token_list *token, int *i, t_env *m_env)
{
	if (*i != 0)
		return (true);
	if (token->type != WORD && token->type != REDIRECTION
		&& token->type != LEFTPAREN)
		return (true);
	while (token != NULL)
	{
		if (token->next && ft_strcmp(token->lexeme, "<<") == 0)
		{
			if (run_herdoc(token->next, m_env) == false)
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

void	expand_delemeter(char **delemeter, int *state)
{
	char	*old_delemeter;

	if (**delemeter !='\'' && **delemeter != '"')
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

void	herdoc_child(char *filename, t_token_list *token, t_env *m_env)
{
	char	*heredoc;
	int		fd;
	int		state;

	rl_catch_signals = 1;
	state = 0;
	expand_delemeter(&token->lexeme, &state);
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
			if (state == 1 && heredoc[0] != '\0')
				expende_dollar(&heredoc, m_env);
			write(fd, heredoc, ft_strlen(heredoc));
			write(fd, "\n", 1);
		}
	}
	exit(0);
}
