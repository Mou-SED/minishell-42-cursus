/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_scan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:11:40 by zaabou            #+#    #+#             */
/*   Updated: 2022/07/22 14:58:04 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool    unclosed_quote(char *lexeme, char quote_type)
{
    if (*lexeme == '\0' && quote_type != 0)
        return (true);
    else if (*lexeme == '\0')
        return (false);
    if (*lexeme == '\'' || *lexeme == '"')
    {
        if (*lexeme == quote_type)
            return (unclosed_quote(++lexeme , 0));
        else if (quote_type == 0)
            return (unclosed_quote(&lexeme[1], *lexeme));
        else
            return (unclosed_quote(&lexeme[1], quote_type));
    }
    else
        return (unclosed_quote(++lexeme, quote_type));
}

static int get_first_quote(char *lexeme, int *index)
{
    if (*lexeme == '\0')
        return (0);
    else if (*lexeme == '\'' || *lexeme == '"')
        return (*index);
    else
    {
        (*index)++;
        return(get_first_quote(++lexeme, index));
    }
    return (*index);
}

bool    check_syntax_error(t_token_list *node)
{
    int index;

    if (node->type != WORD && node->type != REDIRECTION
        && node->type != LEFTPAREN)
        return (ft_print_error(node->lexeme), false);
    while (node != NULL)
    {
        index = 0;
        if ((node->type != WORD && node->type != RIGHTPAREN
            && node->type != REDIRECTION) && node->next == NULL)
            return (ft_print_error(node->lexeme), false);
        else if (node->type == WORD
            && unclosed_quote(&node->lexeme[get_first_quote(node->lexeme,
                &index) + 1], node->lexeme[index]) == true)
            return (ft_print_error("unclosed_quote"), false);
        else if (node->next && node->type == REDIRECTION
            && node->next->type != WORD)
            return (ft_print_error(node->next->lexeme), true);
        else if (node->next && (node->type == OPERATOR || node->type == PIPE)
            && (node->next->type != WORD && node->next->type != LEFTPAREN
                && node->next->type != REDIRECTION))
            return (ft_print_error(node->next->lexeme), true);
        node = node->next;
    }
    return (true);
}
