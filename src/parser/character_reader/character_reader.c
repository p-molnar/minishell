/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_reader.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:40:20 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/21 14:40:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

char	*read_prompt(char *prompt)
{
	char	*prompt_read;

	prompt_read = readline(prompt);
	add_history(prompt_read);
	return (prompt_read);
}
