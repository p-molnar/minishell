/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:49:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/01 17:13:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <ms_data_types.h>
#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>

char	*get_token_end(char *start)
{
	char	*curr;

	curr = start;
	if (*curr == QUOTE || *curr == DQUOTE)
		return (ft_strchr((start + 1), *start));
	while (*curr)
	{
		if (!ft_strchr(OPERATORS, *curr) && ft_strchr(DELIM_CHARS, *(curr + 1)))
			return (curr);
		else if (ft_strchr(OPERATORS, *curr)
			&& !ft_strchr(OPERATORS, *(curr + 1)))
			return (curr);
		else
			curr++;
	}
	return (curr);
}

t_token_list	*tokenizer(const char *prompt)
{
	char			*tkn_start_ptr;
	char			*tkn_end_ptr;
	char			*content;
	t_token_list	*tokens;

	tkn_start_ptr = (char *) prompt;
	tokens = NULL;
	while (*tkn_start_ptr != '\0')
	{
		if (!ft_strchr(SPACES, *tkn_start_ptr))
		{
			tkn_end_ptr = get_token_end(tkn_start_ptr);
			if (tkn_end_ptr == NULL || *tkn_end_ptr == '\0')
				tkn_end_ptr = tkn_start_ptr + ft_strlen(tkn_start_ptr) - 1;
			content = ft_substr(tkn_start_ptr, 0, tkn_end_ptr - tkn_start_ptr + 1);
			add_node_last(&tokens, new_node(content, tkn_start_ptr, UNDEFINED));
			tkn_start_ptr += tkn_end_ptr - tkn_start_ptr;
		}
		tkn_start_ptr++;
	}
	return (tokens);
}
