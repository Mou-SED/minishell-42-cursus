/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:44:04 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/26 16:09:46 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parce_parenteses(t_token_list *token); //TODO : ADD prototype to our Header file
t_ast	*building_ast(t_ast *root, t_token_list *token_list); //TODO : ADD prototype to our Header file

t_ast	*parce_parenteses(t_token_list *token)
{
	t_ast	*root_par;

	root_par = ft_calloc(1, sizeof(t_ast));
	root_par->type = PAR;
	root_par->left = NULL;
	root_par->cmd_node = ft_calloc(1, sizeof(t_cmd));
	root_par->cmd_node->cmd_args = ft_strdup("PARENTESES");
	root_par->right = building_ast(NULL, token->next);
	return (root_par);
}

t_token_list	*get_next_operator(t_token_list *token_list)
{
	if (token_list == NULL || token_list->type == OPERATOR || token_list->type == RIGHTPAREN || token_list->type == LEFTPAREN)
		return (token_list);
	else
		return (get_next_operator(token_list->next));
}
char	*ft_strjoin_char(char *s1, char const *s2, char c)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	newstr = (char *)malloc((sizeof(char)
				* (ft_strlen(s1) + ft_strlen(s2) + 2)));
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		newstr[i] = s1[i];
	free(s1);
	newstr[i++] = c;
	j = 0;
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}

t_ast	*ft_cmd_parse(t_token_list *token)
{
	t_ast	*node;
	t_ast	*pipe_node;

	if (token->type == LEFTPAREN)
		return (parce_parenteses(token));
	node = ft_calloc(1, sizeof(t_ast)); 
	node->cmd_node = ft_calloc(1, sizeof(t_cmd));
	while (token != NULL && token->type != OPERATOR && token->type != RIGHTPAREN)
	{
		if (token->type == PIPE)
		{
			pipe_node = ft_calloc(1, sizeof(t_ast));
			pipe_node->type = PIP;
			pipe_node->left = node;
			pipe_node->right = ft_cmd_parse(token->next);
			printf("the right of pipe is %s\n", pipe_node->right->cmd_node->cmd_args);
			return (pipe_node);
		}
		if (token->type == REDIRECTION)
		{
			node->type = CMD;
			if (ft_strcmp(token->lexeme, "<") == 0 || ft_strcmp(token->lexeme, ">") == 0 || ft_strcmp(token->lexeme, ">>") == 0)
			{
				if (node->cmd_node->redir_files == NULL)
					node->cmd_node->redir_files = ft_strdup(token->lexeme);
				else
					node->cmd_node->redir_files = ft_strjoin_char(node->cmd_node->redir_files, token->lexeme, ' ');
				node->cmd_node->redir_files = ft_strjoin_char(node->cmd_node->redir_files, token->next->lexeme, ' ');
			}
			token = token->next;
		}
		else if (token->type == WORD)
		{
			node->type = CMD;
			if (node->cmd_node->cmd_args == NULL)
				node->cmd_node->cmd_args = ft_strdup(token->lexeme);
			else
				node->cmd_node->cmd_args = ft_strjoin_char(node->cmd_node->cmd_args, token->lexeme, ' ');
		}
		token = token->next;
	}
	return (node);
}

t_token_list	*skip_to_right_parentheses(t_token_list *token); //TODO : ADD prototype to our Header file

t_token_list	*skip_to_right_parentheses(t_token_list *token)
{
	if (token == NULL)
		return (NULL);
	if (token->type == LEFTPAREN)
		token = skip_to_right_parentheses(token->next);
	if (token && token->type == RIGHTPAREN)
		return (token->next);
	if (token)
		return (skip_to_right_parentheses(token->next));
	return (NULL);
}

t_ast	*building_ast(t_ast *root, t_token_list *token_list)
{
	t_ast *current_node;

	if (token_list == NULL || token_list->type == RIGHTPAREN)
		return (root);
	if (token_list->type == OPERATOR)
	{
		current_node = ft_calloc(1, sizeof(t_ast));
		if (ft_strcmp(token_list->lexeme, "&&") == 0)
			current_node->type = AND;
		else
			current_node->type = OR;
		if (current_node->left == NULL)
			current_node->left = root;
		root = current_node;
		current_node->right = ft_cmd_parse(token_list->next);
		if (token_list->next && token_list->next->type == LEFTPAREN)
			token_list = skip_to_right_parentheses(token_list->next->next);
		else
			token_list = get_next_operator(token_list->next);
	}
	else
	{
		root = ft_cmd_parse(token_list);
		if (root->type == PAR)
			token_list = skip_to_right_parentheses(token_list->next);
		else
			token_list = get_next_operator(token_list);
	}
	return (building_ast(root, token_list));
}

void	parsing(void)
{
	printf("parsing\n");
}
