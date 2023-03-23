/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:47:47 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/23 16:56:56 by jzaremba      ########   odam.nl         */
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
	int i;
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

void	print_variables(t_list *list, char *heading)
{
	t_var *var;
	// int		i;

	// i = 0;
	(void)heading;
	while (list)
	{
		// if (!i)
		// 	printf("\n%s\n", heading);
		var = list->content;
		// printf("#%i\t%s=%s\n", i + 1, var->name, var->val);
		printf("%s=%s\n", var->name, var->val);
		list = list->next;
		// i++;
	}
}

void	print_commands(t_command_list *list)
{
	int i;
	const char *symbol[8] = {"COMMAND", "ARGUMENT", "ASSIGNMENT", "OUTFILE",
							 "OUTFILE_APPEND", "INFILE", "HEREDOC DELIMITER", "PIPE"};

	i = 0;
	while (list)
	{
		printf("#%d : -> %s\n", i + 1, symbol[list->symbol]);
		if (list->token)
			printf("%s\n", list->token->content);
		i++;
		list = list->next;
	}
}

void	cleanup_before_exit(t_shell_data *data)
{
	tcsetattr(0, 0, &data->original_termios);
	clear_history();
}

void	initialise_data(t_shell_data *data)
{
	data->env_vars = NULL;
	data->shell_vars = NULL;
	data->prompt = NULL;
	data->tokens = NULL;
	tcgetattr(0, &data->original_termios);
}

int	main(int argc, char *argv[], char *envp[])
{
	int prog_running;
	t_shell_data data;
	// t_command_list *commands;
	(void)argc;
	(void)argv;
	// (void) envp;

	prog_running = 1;
	initialise_data(&data);
	parse_env_variable(envp, &data.env_vars);
	// print_variables(data.env_vars, "ENV VARS");
	while (prog_running)
	{
		setup_signal_handler(&data);
		data.prompt = read_prompt(PROMPT_MSG);
		if (!data.prompt)
			break;
		// printf("original prompt |%s|\n", data.prompt);
		data.tokens = tokenizer(data.prompt);
		parse_shell_variable(&data);
		// print_variables(data.shell_vars, "SHELL VARS");
		classify_tokens(data.tokens);
		commands = parse_commands(data.tokens);
		if (commands)
		{
			expand_tokens(&data);
			// if (ft_strncmp(data.prompt, "export", ft_strlen("export")) == 0)
			// 	export(data.tokens->next, &data);
			// else if (ft_strncmp(data.prompt, "env", ft_strlen("env")) == 0)
			// 	env(data.env_vars);
			// else if (ft_strncmp(data.prompt, "set", ft_strlen("set")) == 0)
			// 	print_variables(data.shell_vars, "SHELL VARS");
			// else if (ft_strncmp(data.prompt, "unset", ft_strlen("unset")) == 0)
			// 	unset(data.tokens->next->content, &data);
			// else if (ft_strncmp(data.prompt, "pwd", ft_strlen("pwd")) == 0)
			// 	pwd(&data);
			// else if (ft_strncmp(data.prompt, "cd", ft_strlen("cd")) == 0)
			// {
			// 	if (!data.tokens->next)
			// 		cd(NULL, &data);
			// 	else
			// 	{
			// 		cd(data.tokens->next->content, &data);
			// 	}
			// }
			// else if (ft_strncmp(data.prompt, "echo", ft_strlen("echo")) == 0)
			// {
			// 	t_token_list *tokens = data.tokens;
			// 	echo(tokens);
			// }
			// print_tokens(data.tokens);
			// print_commands(commands);
			executor(&data, commands);
			free_command_list(commands);
		}
		free_list(data.tokens);
		free(data.prompt);
	}
	cleanup_before_exit(&data);
	free_var_list(data.env_vars);
	free_var_list(data.shell_vars);
	return (0);
}
