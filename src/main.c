/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/07 17:09:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <ms_data_types.h>
#include <termios.h>
#include <readline/history.h>

void	print_tokens(t_token_list *list)
{
	int			i;
	// const char	*token[4] = {"UNDEF", "INVALID", "WORD", "OPERATOR"};

	i = 0;
	while (list)
	{
		// printf("#%d\t:%s: ->%s\n", i + 1, list->content, token[list->type + 1]);
		printf("%s\n", list->content);
		// printf("token_start -> :%s:\n", list->prompt_ptr);
		i++;
		list = list->next;
	}
}

void	cleanup_before_exit(struct termios *original_termios)
{
	tcsetattr(0, 0, original_termios);
	clear_history();
}

int	main(void)
{
	int				prog_running;
	t_shell_data	data;
	// t_token_list	*tokens;
	struct termios	original_termios;

	prog_running = 1;
	setup_signal_handler(&original_termios);
	while (prog_running)
	{
		data.prompt = read_prompt(PROMPT_MSG);
		if (!data.prompt)
			break ;
		printf("original prompt |%s|\n", data.prompt);
		data.tokens = tokenizer(data.prompt);
		classify_tokens(data.tokens);
		expand_tokens(data.tokens);
		print_tokens(data.tokens);
		free_list(data.tokens);
		free(data.prompt);
	}
	cleanup_before_exit(&original_termios);
	return (0);
}
