/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/20 23:13:11 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	waiting_for_my_children(void)
{
	while (wait(&status) != -1)
	{
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            status = WTERMSIG(status) + 128;
    }
}

void	wait_for_one_child(pid_t pid)
{
	while (waitpid(pid, &status, WNOHANG) != -1);
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
	int				i;

	(void)ac;
	(void)av;
	
	head = ft_calloc(1, sizeof(t_token_list *));
	m_env = ft_calloc(1, sizeof(t_env *));
	(*m_env = ft_calloc(1, sizeof(t_env)), build_env(*m_env, env));
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		if (cmd != NULL && *cmd != 0)
		{
			(add_history(cmd), *head = ft_lstnew_token(NULL));
			(tokenizer(skip_space(cmd), head), free(cmd));
			if ((*head)->lexeme == NULL || (check_syntax_error(*head, &i) == true
					&& her_doc(*head, &i) == true))
			{
				status = 258;
				signals_handler();
				ft_lstclear_tokens(head, &free);
				continue ;
			}
			root = building_ast(root, *head, m_env);
			execution(root);
			(ft_lstclear_tokens(head, &free), clear_ast(root));
			waiting_for_my_children();
			// system("leaks minishell");
		}
		else if (cmd == NULL)
			ctl_d_handler(head);
		else if (*cmd == '\0')
			free(cmd);
	}
}
