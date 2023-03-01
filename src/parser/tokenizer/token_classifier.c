/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_classifier.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 10:58:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/01 16:57:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>

static int	is_valid_quotation(char *s)
{
	return (*s == *(s + ft_strlen(s) - 1));
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
