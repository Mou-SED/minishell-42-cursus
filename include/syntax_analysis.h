/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:12 by zaabou            #+#    #+#             */
/*   Updated: 2022/08/11 19:31:45 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYSIS_H
# define SYNTAX_ANALYSIS_H
# include "minishell.h"

typedef enum e_node
{
	AND,
	OR,
	CMD,
	PIP,
	PAR
}	t_node;

typedef	enum e_file
{
	W_TRUNC,
	W_APPRND,
	READ,
}	t_r;

typedef struct files
{
	char	*filename;
	t_r		mode;
	struct files *next;
	
}t_lst;


typedef struct s_cmd
{
	char	**cmd_table;
	char	**paths;
	char	*cmd_args;
	t_lst	*files;
	char	*heredoc;
	int		unused_pipe_fd;
	int		fdin;
	int		fdout;
}	t_cmd;

typedef struct s_ast
{
	t_node			type;
	struct s_ast	*right;
	struct s_ast	*left;
	t_cmd			*cmd_node;
}	t_ast;

// AST functions
t_ast			*ft_ast_new(t_token_list	*token);
t_ast			*building_ast(t_ast *root, t_token_list *token_list);
t_ast			*parse_operator(t_ast *root, t_token_list *token_list);
t_ast			*parse_parenteses(t_ast *node, t_token_list *token);
t_ast			*parse_cmd(t_token_list *token);
t_ast			*parse_pipe(t_ast *root, t_token_list *token);

// Memory Management functions
void			clear_ast(t_ast *root);

// Helper functions
void			join_cmd_args(t_ast *node, t_token_list *token);
t_token_list	*join_files(t_ast *node, t_token_list *token);
t_token_list	*get_next_to_parse(t_token_list *token);
char			*ft_strjoin_char(char *s1, char const *s2, char c);
#endif