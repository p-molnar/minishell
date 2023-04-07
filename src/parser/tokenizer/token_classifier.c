/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_classifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 10:58:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 11:41:56 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>

static int	classify_token(char *s)
{
	if (!ft_strchr(DELIM_CHARS, *s))
		return (WORD);
	else if ((*s == QUOTE || *s == DQUOTE) && is_quote_closed(s, NULL))
		return (WORD);
	else if (ft_strchr(OPERATORS, *s) && is_valid_operator_seq(s))
		return (OPERATOR);
	return (INVALID);
}

void	classify_tokens(t_token_list *list)
{
	int	type;

	while (list)
	{
		type = classify_token(list->content);
		list->type = type;
		list = list->next;
	}
}
