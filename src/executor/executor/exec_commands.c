/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:34:30 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/30 14:00:55 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void	execute_bin(char *command, t_shell_data *data, char	**arguments)
{
	char	**path;
	char	**env;
	char	*commandpath;
	int		i;

	path = path_builder(data, command);
	env = env_builder(data->env_vars);
	i = 0;
	if (path)
	{
		while (path[i])
		{
			commandpath = ft_strjoin(path[i], command);
			execve(commandpath, arguments, env);
			free(commandpath);
			commandpath = NULL;
			i++;
		}
	}
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
}

void	execute_cmd(t_command_list *current, t_shell_data *data,
						t_pipe_fd *in_pipe, t_pipe_fd *out_pipe)
{
	char				**arguments;
	t_token_list		*command;
	t_redir_data		redir_data;

	redir_data.fd_in = -1;
	redir_data.fd_out = -1;
	redir_data.og_stdin = dup(STDIN_FILENO);
	signal(SIGINT, SIG_DFL);
	tcsetattr(0, 0, &data->original_termios);
	redirect_pipes(in_pipe, out_pipe);
	if (redirect_files(current, &redir_data, data))
		exit (1);
	command = get_next_command(current);
	arguments = compound_args(current);
	if (command)
	{
		execute_builtin(command->content, data, arguments);
		execute_bin(command->content, data, arguments);
	}
	exit(127);
}

void	execute_commands(t_command_list *current, t_pipe_fd *pipe_fd,
							pid_t *process, t_shell_data *data)
{
	int				i;
	int				pipe_n;
	t_pipe_fd		*in_pipe;
	t_pipe_fd		*out_pipe;
	t_command_list	*start_of_simple_cmd;

	i = 0;
	pipe_n = count_symbols(D_PIPE, current);
	in_pipe = NULL;
	start_of_simple_cmd = current;
	while (current)
	{
		if (i < pipe_n && pipe_fd)
			out_pipe = &pipe_fd[i];
		else
			out_pipe = NULL;
		if (current->symbol == D_PIPE || current->next == NULL)
		{
			process[i] = fork();
			if (process[i] == 0)
				execute_cmd(start_of_simple_cmd, data, in_pipe, out_pipe);
			i++;
			close_pipe(in_pipe);
			start_of_simple_cmd = current->next;
			if (out_pipe)
				in_pipe = out_pipe;
		}
		current = current->next;
	}
}
