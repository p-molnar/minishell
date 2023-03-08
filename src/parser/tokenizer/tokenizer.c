/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:49:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/28 16:26:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <ms_data_types.h>
#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>

char	*get_string_end(char *start)
{
	char	*curr;

	curr = start;
	if (*curr == QUOTE || *curr == DQUOTE)
		return (ft_strchr((start + 1), *start));
	while (*curr)
	{
		if (!ft_strchr(OPERATORS, *curr) && ft_strchr(META_CHARS, *(curr + 1)))
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
	char			*start_ptr;
	char			*end_ptr;
	char			*content;
	t_token_list	*tokens;

	start_ptr = (char *) prompt;
	tokens = NULL;
	while (*start_ptr != '\0')
	{
		start_ptr = ft_strtrim(start_ptr, SPACES);
		end_ptr = get_string_end(start_ptr);
		if (end_ptr == NULL || *end_ptr == '\0')
			end_ptr = start_ptr + ft_strlen(start_ptr) - 1;
		content = ft_substr(start_ptr, 0, end_ptr - start_ptr + 1);
		add_node_last(&tokens, new_node(content, UNDEFINED));
		start_ptr += end_ptr - start_ptr + 1;
	}
	return (tokens);
}
