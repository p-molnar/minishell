/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/27 23:20:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <ms_data_types.h>

void	print_tokens(t_token_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("#%d :%s:\n", i + 1, list->content);
		i++;
		list = list->next;
	}
}

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
		print_tokens(tokens);
		free(prompt);
	}
	return (0);
}
