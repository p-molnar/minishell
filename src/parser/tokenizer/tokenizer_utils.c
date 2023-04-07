/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 13:11:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 11:43:22 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>

int	is_valid_operator_seq(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 1 || len > 2)
		return (0);
	return (ft_strncmp(DLESS, s, len) == 0
		|| ft_strncmp(DGREAT, s, len) == 0
		|| ft_strncmp("||", s, len) == 0);
}

int	is_quote_closed(char *s, char *quote_to_be_closed)
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
	if (quote_to_be_closed)
		*quote_to_be_closed = in_quote;
	return (in_quote == 0);
}
