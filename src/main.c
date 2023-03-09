/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/09 13:48:28 by pmolnar       ########   odam.nl         */
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

void	print_commands(t_command_list *list)
{
	int			i;
	const char	*symbol[7] = {"COMMAND", "ARGUMENTS", "ASSIGNMENT", "OUTFILE",
								"OUTFILE_APPEND", "INFILE", "PIPE"};

	i = 0;
	while (list)
	{
		printf("#%d : -> %s\n", i + 1, symbol[list->symbol]);
		print_tokens(list->token);
		i++;
		list = list->next;
	}
}

void	print_commands(t_command_list *list)
{
	int			i;
	const char	*symbol[7] = {"COMMAND", "ARGUMENTS", "ASSIGNMENT", "OUTFILE",
								"OUTFILE_APPEND", "INFILE", "PIPE"};

	i = 0;
	while (list)
	{
		printf("#%d : -> %s\n", i + 1, symbol[list->symbol]);
		print_tokens(list->token);
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
	char			*prompt;
	int				prog_running;
	t_token_list	*tokens;
	t_command_list	*commands;
	struct termios	original_termios;

	prog_running = 1;
	setup_signal_handler(&original_termios);
	while (prog_running)
	{
		prompt = read_prompt(PROMPT_MSG);
		if (!prompt)
			break ;
		printf("original prompt |%s|\n", prompt);
		tokens = tokenizer(prompt);
		classify_tokens(tokens);
		commands = parse_commands(tokens);
		expand_tokens(tokens);
		print_tokens(tokens);
		print_commands(commands);
		free_command_list(commands);
		free_list(tokens);
		free(prompt);
	}
	cleanup_before_exit(&original_termios);
	return (0);
}
