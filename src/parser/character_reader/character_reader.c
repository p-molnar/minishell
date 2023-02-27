/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_reader.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:40:20 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/27 16:21:46 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*read_prompt(char *prompt)
{
	char	*prompt_read;

	prompt_read = NULL;
	prompt_read = readline(prompt);
	if (prompt_read)
	{
		if (ft_strncmp(prompt_read, "", 1))
			add_history(prompt_read);
	}
	return (prompt_read);
}
