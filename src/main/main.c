/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/23 17:50:50 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	allocate_memory(t_token_list ***head, t_env ***m_env,
	char **env, char **pwd)
{
	*head = ft_calloc(1, sizeof(t_token_list *));
	if (*head == NULL)
		allocation_faild();
	*m_env = ft_calloc(1, sizeof(t_env *));
	if (*m_env == NULL)
		allocation_faild();
	**m_env = ft_calloc(1, sizeof(t_env));
	if (**m_env == NULL)
		allocation_faild();
	*pwd = getcwd(NULL, 0);
	build_env(**m_env, env);
}

void	waiting_for_my_children(void)
{
	signal(SIGINT, SIG_IGN);
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			printf("\n");
			status = WTERMSIG(status) + 128;
		}
	}
	signals_handler();
}

void	wait_for_one_child(pid_t pid)
{
	while (waitpid(pid, &status, WNOHANG) != -1)
		;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
}

int	main(int ac, char **av, char **env)
{
	char			*cmd;
	t_token_list	**head;
	t_ast			*root;
	t_env			**m_env;
	char			*cwd;
	int				i;

	(void)ac;
	(void)av;
	allocate_memory(&head, &m_env, env, &cwd);
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		if (cmd != NULL && *cmd != 0)
		{
			(add_history(cmd), *head = ft_lstnew_token(NULL));
			(tokenizer(skip_space(cmd), head), free(cmd));
			if ((*head)->lexeme == NULL || (check_syntax_error(*head, &i)
					== true && her_doc(*head, &i, *m_env) == true))
			{
				(signals_handler(), ft_lstclear_tokens(head, &free));
				continue ;
			}
			root = building_ast(root, *head, m_env);
			execution(root, &cwd);
			(ft_lstclear_tokens(head, &free), clear_ast(root));
			waiting_for_my_children();
		}
		else if (cmd == NULL)
			ctl_d_handler(head, m_env, cwd);
		else if (*cmd == '\0')
			free(cmd);
		system("leaks minishell");
	}
}
