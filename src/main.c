/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/27 16:31:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <ms_data_types.h>

int	main(void)
{
	char			*prompt;
	int				prog_running;
	t_token_list	*tokens;

	prog_running = 1;
	while (prog_running)
	{
		prompt = read_prompt(PROMPT_MSG);
		printf("original prompt |%s|\n", prompt);
		tokens = tokenizer(prompt);
		free(prompt);
	}
	return (0);
}
