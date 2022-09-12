/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:53:14 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 12:32:30 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	out_files(t_ast *node, t_lst *tmp)
{
	if (node->cmd_node->fdout != 1)
		close(node->cmd_node->fdout);
	if (access(tmp->filename, F_OK) != 0)
		node->cmd_node->fdout
			= open(tmp->filename, O_CREAT | O_WRONLY,
				0644);
	else
	{
		if (check_file(tmp->filename, W_TRUNC) == false)
			return (false);
		if (tmp->mode == W_APPRND)
			node->cmd_node->fdout = open(tmp->filename,
					O_WRONLY | O_APPEND);
		if (tmp->mode == W_TRUNC)
			node->cmd_node->fdout = open(tmp->filename,
					O_WRONLY | O_TRUNC);
	}
	if (node->cmd_node->fdout == -1)
		return (redirection_error(tmp->filename, strerror(errno)), false);
	return (true);
}

bool	in_files(t_ast *node, t_lst *tmp)
{
	if (node->cmd_node->fdin != 0)
		close(node->cmd_node->fdin);
	if (check_file(tmp->filename, READ) == false)
		return (false);
	node->cmd_node->fdin
		= open(tmp->filename, O_RDONLY);
	return (true);
}

bool	expande_files_name(char **filename, t_env *m_env)
{
	char	*old_filename;

	old_filename = ft_strdup(*filename);
	free(*filename);
	*filename = NULL;
	expande_file(&(*filename), old_filename, 0, m_env);
	if (*filename == NULL)
	{
		redirection_error(old_filename, "ambiguous redirect");
		return (free(old_filename), false);
	}
	else if (**filename == '\0')
	{
		redirection_error("", "No such file or directory");
		return (free(old_filename), false);
	}
	return (free(old_filename), true);
}

void	expande_file(char **update_str, char *str, int state, t_env *m_env)
{
	if (*str == '\0')
		return ;
	if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '\0'
		&& is_not_special_char(*(str + 1)))
		str = expande_var_file_name(&(*update_str), ++str, m_env);
	else if (*str == '\'' && state == 0)
		str = single_quote_case(&(*update_str), ++str);
	else if (*str != '"')
		ft_update_str(&(*update_str), *str);
	if (*str == '"')
	{
		if (state == 0)
		{
			if (*update_str == NULL)
				*update_str = ft_strdup("");
			state = 1;
		}
		else
			state = 0;
	}
	expande_file(&(*update_str), ++str, state, m_env);
}

char	*expande_var_file_name(char **update_str, char *str, t_env *m_env)
{
	int		i;
	char	*var_value;
	char	*var_name;

	i = 0;
	i = skip_dollars(str);
	if (str[i] == '?')
	{
		if (str[++i] != '\0' && str[i] != '$')
			i++;
		var_value = ft_itoa(g_status);
	}
	else
	{
		while (str[i] != '\0' && str[i] != '"' && str[i] != '\''
			&& str[i] != '$' && str[i] != ' ' && is_not_special_char(str[i]))
			i++;
		var_name = ft_substr(str, 0, i);
		var_value = get_variable(m_env, var_name);
		free(var_name);
	}
	if (var_value != NULL)
		*update_str = join_expended_str(*update_str, var_value);
	return (free(var_value), (str + i) - 1);
}
