/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/08/15 16:18:54 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_variable(t_env **m_env, t_env *var)
{
	t_env	*tmp;

	tmp = *m_env;
	if (tmp == NULL)
		tmp = var;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = var;
}

void	create_own_env(t_env **m_env, char **env)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = -1;
	tmp = ft_calloc(1, sizeof(t_env));
	*m_env = tmp;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		tmp->variable = ft_calloc((j + 1), sizeof(char));
		ft_memcpy(tmp->variable, env[i], j);
		if (ft_strcmp(tmp->variable, "SHELL") == 0)
			tmp->value = ft_strdup("minishell");
		else
			tmp->value = ft_strdup(&env[i][j + 1]);
		if (env[i] && env[i + 1])
			tmp->next = ft_calloc(1, sizeof(t_env));
		tmp = tmp->next;
	}		
}

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
	create_own_env(m_env, env);
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
				ft_lstclear_tokens(head, &free);
				continue ;
			}
			root = building_ast(root, *head, m_env);
			execution(root);
			(ft_lstclear_tokens(head, &free), clear_ast(root));
			waiting_for_my_children();
		}
		else if (cmd == NULL)
			ctl_d_handler(head);
	}
}
