/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:49:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 09:50:42 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <ms_data_types.h>
#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>

static void	update_prev_ptr(char **prev, char *curr, char *s)
{
	if (curr != s)
		*prev = curr - 1;
	else
		*prev = curr;
}

static char	*is_token_end(char *prev, char *curr, char *is_quoted)
{

	if (!*is_quoted && ft_strchr(OPERATORS, *prev) && *curr == *prev)
		;
	else if (!*is_quoted && ft_strchr(OPERATORS, *prev) && *curr != *prev)
		return (prev);
	else if (!*is_quoted && ft_strchr(QUOTES, *curr))
		*is_quoted = *curr;
	else if (*is_quoted && ft_strchr(QUOTES, *curr) && *curr == *is_quoted)
		*is_quoted = 0;
	else if (!*is_quoted && ft_strchr(OPERATORS, *curr))
		return (prev);
	else if (!*is_quoted && *curr == ' ')
		return (prev);
	return (NULL);
}

char	*delimit_token(char *prompt)
{
	char	*curr;
	char	*prev;
	char	*tkn_end;
	char	quote;

	curr = prompt;
	while (curr && *curr != '\0')
	{
		update_prev_ptr(&prev, curr, prompt);
		tkn_end = is_token_end(prev, curr, &quote);
		if (tkn_end)
			return (tkn_end);
		curr++;
	}
	return (curr - 1);
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
			end_ptr = delimit_token(start_ptr);
			content = ft_substr(start_ptr, 0, end_ptr - start_ptr + 1);
			add_node_last(&tokens, new_node(content, UNDEFINED));
			start_ptr += end_ptr - start_ptr;
		}
		start_ptr++;
	}
	return (tokens);
}
