/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_reader.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:40:20 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/11 14:03:10 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*read_until_delim(char *s, char delim)
{
	char	*tmp;
	char	*prompt;
	int		matching_quote_found;

	matching_quote_found = 0;
	tmp = NULL;
	signal(SIGINT, handle_quote_int_signal);
	if (!s)
		return (NULL);
	while (!matching_quote_found)
	{
		prompt = readline("> ");
		if (!prompt)
			return (NULL);
		if (ft_strchr(prompt, delim))
			matching_quote_found = 1;
		if (*s != '\n')
			s = strconcat(3, s, "\n", prompt);
		else
			s = strconcat(4, "\n", s, "\n", prompt);
		free_obj((void **)&prompt);
		free_obj((void **)&tmp);
		tmp = s;
	}
	return (s);
}

char	*read_prompt(const char *prompt)
{
	char	*prompt_read;
	char	*tmp;
	char	delimiter;

	prompt_read = NULL;
	prompt_read = readline(prompt);
	if (prompt_read)
	{
		while (!is_quote_closed(prompt_read, &delimiter))
		{
			tmp = prompt_read;
			prompt_read = read_until_delim(prompt_read, delimiter);
			free_obj((void **)&tmp);
		}
		if (prompt_read && prompt_read[0] != '\0')
			add_history(prompt_read);
	}	
	return (prompt_read);
}
