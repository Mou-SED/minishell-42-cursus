/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:48:12 by zaabou            #+#    #+#             */
/*   Updated: 2022/09/10 00:09:27 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYSIS_H
# define SYNTAX_ANALYSIS_H
# include <minishell.h>

typedef enum e_node
{
	AND,
	OR,
	CMD,
	PIP,
	PAR
}	t_node;

typedef enum e_file
{
	W_TRUNC,
	W_APPRND,
	READ,
	HERE_DOC_FILE_NAME
}	t_r;

typedef struct files
{
	char			*filename;
	t_r				mode;
	struct files	*next;
}t_lst;

typedef struct s_cmd
{
	char	**cmd_table;
	char	**paths;
	char	*cmd_args;
	t_env	**m_env;
	t_lst	*files;
	char	*heredoc;
	int		unused_pipe_fd;
	int		fdin;
	int		fdout;
	bool	wait;
}	t_cmd;

typedef struct s_ast
{
	t_node			type;
	struct s_ast	*right;
	struct s_ast	*left;
	t_cmd			*cmd_node;
}	t_ast;

// AST functions
t_ast			*ft_ast_new(t_token_list	*token, t_env **m_env);
t_ast			*building_ast(t_ast *root, t_token_list *token, t_env **m_env);
t_ast			*parse_operator(t_ast *root, t_token_list *token,
					t_env **m_env);
t_ast			*parse_parenteses(t_ast *node, t_token_list *token,
					t_env **m_env);
t_ast			*parse_cmd(t_token_list *token, t_env **m_env);
t_ast			*parse_pipe(t_ast *node, t_token_list *token, t_env **m_env);

// Memory Management functions
void			clear_ast(t_ast *root);
void			free_table(char **table);

// Helper functions
void			join_cmd_args(t_ast *node, t_token_list *token);
t_token_list	*join_files(t_ast *node, t_token_list *token);
t_token_list	*get_next_to_parse(t_token_list *token);
char			*ft_strjoin_char(char *s1, char const *s2, char c);
bool			unclosed_quote(char *lexeme, char quote_type);
int				get_first_quote(char *lexeme, int index);
#endif