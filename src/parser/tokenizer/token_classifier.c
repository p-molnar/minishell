/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_classifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 10:58:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/03 15:02:23 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>

static int	is_valid_quotation(char *s)
{
	int	in_quote;

	in_quote = 0;
	while (s && *s)
	{
		if (!in_quote && ft_strchr(QUOTES, *s))
			in_quote = *s;
		else if (in_quote && in_quote == *s)
			in_quote = 0;
		s++;
	}
	return (in_quote == 0);
}

static int	is_valid_operator_seq(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 1 || len > 2)
		return (0);
	return (ft_strncmp(DLESS, s, len) == 0
		|| ft_strncmp(DGREAT, s, len) == 0
		|| ft_strncmp("||", s, len) == 0);
}

static int	classify_token(char *s)
{
	if (!ft_strchr(DELIM_CHARS, *s))
		return (WORD);
	else if ((*s == QUOTE || *s == DQUOTE) && is_valid_quotation(s))
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
