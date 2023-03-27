/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:49:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/27 11:31:33 by pmolnar       ########   odam.nl         */
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
	char	is_quoted;
	char	*curr;

	is_quoted = 0;
	curr = start;
	while (*curr != '\0' && (*(curr + 1) != ' ' || is_quoted))
	{
		if (*curr == QUOTE || *curr == DQUOTE)
		{
			if (!is_quoted)
				is_quoted = *curr;
			else if (is_quoted == *curr)
				is_quoted = 0;
		}
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

	start_ptr = (char *)prompt;
	tokens = NULL;
	while (start_ptr && *start_ptr != '\0')
	{
		if (!ft_strchr(SPACES, *start_ptr))
		{
			end_ptr = get_token_end(start_ptr);
			if (end_ptr == NULL || *end_ptr == '\0')
				end_ptr = start_ptr + ft_strlen(start_ptr) - 1;
			content = ft_substr(start_ptr, 0, end_ptr - start_ptr + 1);
			add_node_last(&tokens, new_node(content, start_ptr, UNDEFINED));
			start_ptr += end_ptr - start_ptr;
		}
		start_ptr++;
	}
	return (tokens);
}
