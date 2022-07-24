/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:44:04 by moseddik          #+#    #+#             */
/*   Updated: 2022/07/25 00:15:13 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*building_ast(t_ast *root, t_token_list *token_list);
void	print_parse_cmd(t_ast *node);

t_token_list	*get_right_par(t_token_list *token)
{
	if (token == NULL)
		return (token);
	if (token->type == RIGHTPAREN)
		return(token->next);
	if (token->type == LEFTPAREN)
		return (get_right_par(token->next));
	else
		return (get_right_par(token->next));
}

t_token_list	*get_next_token(t_token_list *token_list)
{
	if (token_list == NULL || token_list->type == RIGHTPAREN) 
		return(NULL);
	if(token_list->type == OPERATOR)
		return(token_list);
	else
		return(get_next_token(token_list->next));
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
	t_ast	*paren_node;
	bool	pipe;

	node = ft_calloc(1, sizeof(t_ast));
	node->cmd_node = ft_calloc(1, sizeof(t_cmd));
	while (token != NULL && token->type != OPERATOR)
	{
		if (token->type == RIGHTPAREN)
			break ;
		if (token->type == LEFTPAREN)
		{
			paren_node = ft_calloc(1, sizeof(t_ast));
			paren_node->type = PAREN;
			paren_node->left = NULL;
			paren_node->right = building_ast(paren_node, token->next);
			return(paren_node);
		}
		if (token->type == PIPE)
		{
			pipe = true;
			pipe_node = ft_calloc(1, sizeof(t_ast));
			pipe_node->type = PIP;
			pipe_node->left = node;
			pipe_node->right = ft_cmd_parse(token->next);
			return(pipe_node);
			
		}
		if (token->type == REDIRECTION)
		{
			node->type = CMD;
			if (ft_strcmp(token->lexeme, "<") == 0)
			{
				if (node->cmd_node->in_files == NULL)
					node->cmd_node->in_files = ft_strdup(token->lexeme);
				else
					node->cmd_node->in_files = ft_strjoin_char(node->cmd_node->in_files, token->lexeme, ' ');
				node->cmd_node->in_files = ft_strjoin_char(node->cmd_node->in_files, token->next->lexeme, ' ');
			}
			else if (ft_strcmp(token->lexeme, ">") == 0)
			{
				if (node->cmd_node->out_files == NULL)
					node->cmd_node->out_files = ft_strdup(token->lexeme);
				else
					node->cmd_node->out_files = ft_strjoin_char(node->cmd_node->out_files, token->lexeme, ' ');
				node->cmd_node->out_files = ft_strjoin_char(node->cmd_node->out_files, token->next->lexeme, ' ');
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

t_ast	*building_ast(t_ast *root, t_token_list *token_list)
{
	t_ast *current_node;
	
	current_node = ft_calloc(1, sizeof(t_ast));
	if (token_list == NULL || token_list->type == RIGHTPAREN)
		return (root);
	if (token_list->type == OPERATOR)
	{
		if (ft_strcmp(token_list->lexeme, "&&") == 0)
			current_node->type = AND;
		else
			current_node->type = OR;
		if (current_node->left == NULL)
			current_node->left = root;
		root = current_node;
		current_node->right = ft_cmd_parse(token_list->next);
		token_list = get_next_token(token_list->next);
	}
	else
	{
		root = ft_cmd_parse(token_list);
		if (root->type == PAREN)
			token_list = get_right_par(token_list->next);
		else
			token_list = get_next_token(token_list->next);
	}
	return (building_ast(root, token_list));
}

void	parsing(void)
{
	
	printf("parsing\n");
}
