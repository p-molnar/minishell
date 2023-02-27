/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/27 16:23:28 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <readline/history.h>

void	cleanup_before_exit(struct termios *original_termios)
{
	tcsetattr(0, 0, original_termios);
	clear_history();
}

int	main(void)
{
	char			*prompt;
	struct termios	original_termios;

	setup_signal_handler(&original_termios);
	while (1)
	{
		prompt = read_prompt(PROMPT_MSG);
		if (!prompt)
			break ;
		printf("%s", prompt);
		free(prompt);
	}
	cleanup_before_exit(&original_termios);
	return (0);
}
