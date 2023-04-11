/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/11 10:54:40 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <ms_data_types.h>
#include <termios.h>
#include <readline/history.h>

void	initialise_data(t_shell_data *data)
{
	data->variables = NULL;
	data->prompt = NULL;
	data->tokens = NULL;
	tcgetattr(0, &data->original_termios);
	g_exit_status = 0;
	data->commands = NULL;
	data->oldpwd_set = get_var("OLDPWD", data->variables, ENV) > 0;
}

void	parse_prompt(t_shell_data *data)
{
	data->tokens = tokenizer(data->prompt);
	parse_shell_variable(data);
	classify_tokens(data->tokens);
	data->commands = parse_commands(data->tokens);
}

void	execute_command_list(t_shell_data *data)
{
	expand_tokens(data);
	executor(data, data->commands);
}

void	ignore_fn_arg(int arg1, char **arg2)
{
	(void) arg1;
	(void) arg2;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	data;

	ignore_fn_arg(argc, argv);
	initialise_data(&data);
	parse_env_variable(envp, &data.variables);
	while (1)
	{
		setup_signal_handler(&data);
		data.prompt = read_prompt(PROMPT_MSG);
		if (!data.prompt)
			break ;
		parse_prompt(&data);
		if (data.commands)
		{
			execute_command_list(&data);
			free_command_list(&data.commands);
		}
		free_token_list(data.tokens);
		free(data.prompt);
	}
	cleanup_before_exit(&data);
	free_var_list(data.variables);
	return (EXIT_SUCCESS);
}
