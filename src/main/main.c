/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/25 00:13:01 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ft_cmd_parse(t_token_list *token);
t_ast	*building_ast(t_ast *root, t_token_list *token_list);

void	print_parse_cmd(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->type == PAREN)
		printf("i am (\n");
	if (node->type == OR)
			printf(" im ||\n");		
	else if (node->type == AND)
			printf(" im &&\n");
	if (node->type == PIP)
		printf("the sub_root is |\n");
	if (node->left != NULL)
	{
		if (node->left->type == CMD)
		{
			printf("my left is : %s\n", node->left->cmd_node->cmd_args);
			// printf("my input fils [ %s ]\n", node->left->cmd_node->in_files);
			// printf("my output fils[ %s ]\n", node->left->cmd_node->out_files);
		}
		else if (node->left->type == PIP)
			printf("my left is | \n");
		else
			printf("my left is %u\n", node->left->type);
	}
	if (node->right != NULL)
	{
		if (node->right->type == CMD)
		{
			printf("my right is : %s\n", node->right->cmd_node->cmd_args);
			// printf("my input fils [ %s ]\n", node->right->cmd_node->in_files);
			// printf("my output fils[ %s ]\n", node->right->cmd_node->out_files);
		}
		else if (node->right->type == PIP)
			printf("my right is | \n");
		else
			printf("my right is %u\n", node->right->type);
	}
	print_parse_cmd(node->left);
	print_parse_cmd(node->right);
}

void	ft_print_tokens(t_token_list *head)
{
	char	*str[7] = {"WORD", "PIPE", "REDIRECTION", "OPERATOR",
		"LEFTPAREN", "RIGHTPAREN"};
	if (head == NULL)
		printf("head is Null\n");
	while (head != NULL)
	{
		printf("[%s] --> [%s]\n", head->lexeme, str[head->type]);
		head = head->next;
	}
}

int	main(int ac, char **av)
{
	char			*cmd;
	t_token_list	**head;
	t_ast			*root;

	(void)ac;
	(void)av;
	head = ft_calloc(1, sizeof(t_token_list *));
	root = ft_calloc(1, sizeof(t_ast));
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		if (cmd != NULL && *cmd != 0)
		{
			(add_history(cmd), *head = ft_lstnew_token("content"));
			(tokenizer(skip_space(cmd), head), free(cmd));
			/*if (check_syntax_error(*head) == false)
			{
				ft_lstclear_tokens(head, &free);
				continue ;
			}*/
			root = building_ast(root, *head);
			print_parse_cmd(root);
			//(ft_print_tokens(*head), ft_lstclear_tokens(head, &free));
		}
		else if (cmd == NULL)
			ctl_d_handler(head);
	}
}
