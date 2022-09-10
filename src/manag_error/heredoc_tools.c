/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:41:18 by moseddik          #+#    #+#             */
/*   Updated: 2022/09/10 13:30:08 by zaabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expande_helper(char **herdoc, char *str, t_env *m_env)
{
	if (*str == '\0')
		return ;
	else if (*str == '$')
		str = expande_variable_herdoc(&(*herdoc), ++str, m_env);
	else
		ft_update_str(&(*herdoc), *str);
	expande_helper(&(*herdoc), ++str, m_env);
}

void	expende_dollar(char **herdoc, t_env *m_env)
{
	char	*herdoc_cp;

	herdoc_cp = ft_strdup(*herdoc);
	free(*herdoc);
	*herdoc = NULL;
	expande_helper(&(*herdoc), herdoc_cp, m_env);
	if (*herdoc == NULL)
		*herdoc = ft_strdup("");
	free(herdoc_cp);
	herdoc_cp = NULL;
}

void	expande(char **delemeter, char *old_delemeter, int state)
{
	if (*old_delemeter == '\0')
		return ;
	if (*old_delemeter == '\'' && state == 0)
		old_delemeter = single_quote_case(&(*delemeter), ++old_delemeter);
	else if (*old_delemeter != '"')
		ft_update_str(&(*delemeter), *old_delemeter);
	if (*old_delemeter == '"')
	{
		if (state == 0)
			state = 1;
		else
			state = 0;
	}
	expande(&(*delemeter), ++old_delemeter, state);
}
