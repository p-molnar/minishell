/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_classifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 10:58:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 17:21:10 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>

static int	classify_token(char *s)
{
	int	flags;

	flags = UNDEFINED;
	if (!ft_strchr(DELIM_CHARS, *s))
		flags |= WORD;
	if (ft_strchr(s, QUOTE))
		flags |= S_QUOTED;
	if (ft_strchr(s, DQUOTE))
		flags |= D_QUOTED;
	if (ft_strchr(OPERATORS, *s) && !(ft_strchr(s, QUOTE) || ft_strchr(s, DQUOTE)))
		flags = OPERATOR;
	if (flags & OPERATOR && !is_valid_operator_seq(s))
		flags = INVALID;
	return (flags);
}

void	classify_tokens(t_token_list *list)
{
	int	type;

	while (list)
	{
		type = classify_token(list->content);
		list->type = type;
		// printf("content: %s, type: %i\n", list->content, list->type);
		list = list->next;
	}
}
