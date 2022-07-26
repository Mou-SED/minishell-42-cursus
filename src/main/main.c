/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:48:30 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/26 16:08:23 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*ft_cmd_parse(t_token_list *token); //TODO : ADD prototype to our Header file
t_ast	*building_ast(t_ast *root, t_token_list *token_list); //TODO : ADD prototype to our Header file

//! ****************************************************************************
// #include <fcntl.h>

// void	execution(t_ast *root)
// {
// 	char **infile;
// 	char **outfile;
// 	int i = 0;
// 	if (!fork())
// 	{
// 		if (root->cmd_node->in_files)
// 		{
// 			infile = ft_split(root->cmd_node->in_files, ' ');
// 			while (infile[i] != NULL)
// 			{
// 				if (ft_strcmp(infile[i], "<") == 0)
// 				{
// 					if (infile[i + 1] != NULL)
// 						dup2(open(infile[i + 1], O_RDONLY), 0);
// 					i++;
// 				}
// 				i++;
// 			}
// 			i = 0;
// 		}
// 		if (root->cmd_node->out_files)
// 		{
// 			outfile = ft_split(root->cmd_node->out_files, ' ');
// 			while (outfile[i] != NULL)
// 			{
// 				if (ft_strcmp(outfile[i], ">") == 0)
// 				{
// 					if (outfile[i + 1] != NULL)
// 						dup2(open(outfile[i + 1], O_CREAT | O_WRONLY, 00777), 1);
// 					i++;
// 				}
// 				i++;
// 			}
// 			i = 0;
// 		}
// 		system(root->cmd_node->cmd_args);
// 		exit(0);
// 	}
// 	else
// 		wait(NULL);
// }
//! ****************************************************************************

void	clear_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	if (root->left)
		clear_ast(root->left);	
	if (root->right)
		clear_ast(root->right);
	if (root->cmd_node)
	{
		if (root->cmd_node->cmd_table)
			free(root->cmd_node->cmd_table);
		if(root->cmd_node->cmd_args)
			free(root->cmd_node->cmd_args);
		if(root->cmd_node->redir_files)
			free(root->cmd_node->redir_files);
		free(root->cmd_node);
	}
	free(root);
	root = NULL;
}
void	print_parse_cmd(t_ast *node)
{
	char *str[2] = {"&&", "||"};
	if (node == NULL)
		return ;
	if (node->type == PAR)
		printf("\t\t iam '('\n");
	if (node->type == OR)
			printf("\t\t im ||\n");
	else if (node->type == AND)
			printf("\t\t im &&\n");
	if (node->type == PIP)
		printf("\t\tthe sub_root is |\n");
	if (node->left != NULL)
	{
		if (node->left->type == CMD)
		{
			printf("my left is : %s\n", node->left->cmd_node->cmd_args);
			printf("my input && output files [ %s ]\n", node->left->cmd_node->redir_files);
		}
		else if (node->left->type == PIP)
			printf("my left is | \n");
		else if (node->left->type == PAR)
			printf("im %s\n", node->left->cmd_node->cmd_args);
		else
			printf("my left is %s\n", str[node->left->type]);
	}
	if (node->right != NULL)
	{
		if (node->right->type == CMD)
		{
			printf("\t\t\t\tmy right is : %s\n", node->right->cmd_node->cmd_args);
			printf("my input && output files [ %s ]\n", node->right->cmd_node->redir_files);
		}
		else if (node->right->type == PIP)
			printf("\t\t\t\tmy right is | \n");
		else
			printf("\t\t\t\tmy right is %s\n", str[node->right->type]);
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
	signals_handler();
	while (1)
	{
		cmd = readline("\001\e[1;36m\002MiniShell~ \001\e[0m\002");
		if (cmd != NULL && *cmd != 0)
		{
			(add_history(cmd), *head = ft_lstnew_token("content"));
			(tokenizer(skip_space(cmd), head), free(cmd));
			if (check_syntax_error(*head) == false)
			{
				ft_lstclear_tokens(head, &free);
				continue ;
			}
			root = building_ast(root, *head);
			// execution(*root); //TODO : Delete this line
			print_parse_cmd(root);
			ft_lstclear_tokens(head, &free);
			clear_ast(root);
		}
		else if (cmd == NULL)
			ctl_d_handler(head);
	}
}
