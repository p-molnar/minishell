/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 13:49:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 11:30:34 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <ms_data_types.h>
#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

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
	quote = 0;
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
	t_token_list	*tokens;
	char			*start_ptr;
	char			*end_ptr;
	char			*content;

	tokens = NULL;
	start_ptr = (char *)prompt;
	while (start_ptr && *start_ptr!= '\0')
	{
		if (!ft_strchr(SPACES, *start_ptr))
		{
			end_ptr = delimit_token(start_ptr);
			content = ft_substr(start_ptr, 0, end_ptr - start_ptr + 1);
			if (*content == '\0')
				free(content);
			else
				add_node_last(&tokens, new_node(content, UNDEFINED));
			start_ptr += end_ptr - start_ptr;
		}
		start_ptr++;
	}
	return (tokens);
}
