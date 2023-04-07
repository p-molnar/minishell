/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:34:30 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/07 19:29:33 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

void	test_path(char *path)
{
	struct stat	path_stat;
	int			err_code;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		error("is a directory", EXIT, 126);
	else
	{
		err_code = access(path, F_OK | X_OK);
		if (err_code != 0)
			error(strerror(errno), EXIT, err_code);
	}
}

void	execute_bin(char *command, t_shell_data *data, char	**arguments)
{
	char		**path_arr;
	char		**env;
	char		*path;
	int			i;
	int			err;
	const char	*folder_char = "/";

	path_arr = get_path_to_bin(data, command);
	env = convert_list_to_arr(data->variables, ENV);
	if (*command == '.' || (ft_strnstr(command, folder_char, ft_strlen(command)) && *command != '/'))
	{
		//execute from current directory
		if (*command == '.')
			command++;
		while (*command == '/')
			command++;
		path = strconcat(3, get_var("PWD", data->variables, SHL)->val, "/", command);
		test_path(path);
		err = execve(path, arguments, env);
		error(strerror(errno), EXIT, err);
	}
	else if (*command == '/')
	{
		//execute from absolute path
		test_path(command);
		err = execve(command, arguments, env);
		if (err)
			error(strerror(errno), EXIT, err);
	}
	else if (path_arr)
	{
		//execute from PATH variable
		i = 0;
		while (path_arr[i])
		{
			execve(path_arr[i], arguments, env);
			i++;
		}
	}
	free_arr((void **) path_arr);
	free_arr((void **) env);
}

void	execute_cmd(t_command_list *current, t_shell_data *data,
						t_pipe_fd *in_pipe, t_pipe_fd *out_pipe)
{
	char				**arguments;
	t_token_list		*command;
	t_redir_data		redir_data;

	initialise_redirection_data(&redir_data);
	signal(SIGINT, SIG_DFL);
	tcsetattr(0, 0, &data->original_termios);
	redirect_pipes(in_pipe, out_pipe);
	if (redirect_files(current, &redir_data, data))
		exit (EXIT_FAILURE);
	command = get_next_command(current);
	arguments = compound_args(current);
	if (command)
	{
		execute_builtin(command->content, data, arguments);
		execute_bin(command->content, data, arguments);
	}
	free(arguments);
	error("command not found", EXIT, 127);
}

t_command_list	*get_next_simple_cmd(t_command_list *start)
{
	static t_command_list	*current;

	current = start;
	while (current)
	{
		if (current->symbol == D_PIPE)
		{
			current = current->next;
			return (current);
		}
		current = current->next;
	}
	return (current);
}

void	execute_commands(t_command_list *current, t_pipe_fd *pipe_fd,
							pid_t *process, t_shell_data *data)
{
	int				i;
	t_pipe_fd		*in_pipe;
	t_pipe_fd		*out_pipe;
	t_command_list	*start_of_simple_cmd;

	i = 0;
	in_pipe = NULL;
	start_of_simple_cmd = current;
	while (i < count_symbols(CMD, current))
	{
		if (i < count_symbols(D_PIPE, current) && pipe_fd)
			out_pipe = &pipe_fd[i];
		else
			out_pipe = NULL;
		process[i] = fork();
		if (process[i] == 0)
			execute_cmd(start_of_simple_cmd, data, in_pipe, out_pipe);
		i++;
		close_pipe(in_pipe);
		start_of_simple_cmd = get_next_simple_cmd(start_of_simple_cmd);
		if (out_pipe)
			in_pipe = out_pipe;
	}
}
