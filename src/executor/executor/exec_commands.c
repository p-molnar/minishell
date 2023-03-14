/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:34:30 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/14 17:58:47 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char	**path_builder(void)
{
	char	**path;
	char	*finalpath;
	int		i;

	i = 0;
	//getenv should be replaced with our own function so we get the local PATH
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		finalpath = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = finalpath;
		i++;
	}
	return (path);
}

char	**compound_args(t_command_list *current)
{
	char 	**arguments;
	int		arg_n;
	int		i;

	i = 0;
	arg_n = count_symbols_simple_cmd(ARG, current);
	arguments = malloc(sizeof(char *) * (arg_n + 2));
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == ARG || current->symbol == CMD)
		{
			arguments[i] = current->token->content;
			i++;
		}
		current = current->next;
	}
	arguments[i] = NULL;
	return (arguments);
}

void	execute_bin(char *command, t_shell_data *data, char	**arguments)
{
	char	**path;
	char	*commandpath;
	int		i;

	path = path_builder();
	i = 0;
	//shouldn't set data to null, this is for testing only (prevent compilation error)
	data = NULL;
	while (path[i])
	{
		commandpath = ft_strjoin(path[i], command);
		//env vars should be turned into array of strings and passed instead of NULL
		execve(commandpath, arguments, NULL);
		free(commandpath);
		commandpath = NULL;
		i++;
	}
	free(commandpath);
	ft_putstr_fd("Command not found\n", 2);
	exit(0);
}

void	execute_cmd(t_command_list *current, t_shell_data *data, t_pipe_fd *in_pipe, t_pipe_fd *out_pipe)
{
	char	**arguments;
	redirect_pipes(in_pipe, out_pipe);
	//handle file redirects here, they overwrite the pipe redirects
	arguments = compound_args(current);
	//check for builtin, execute builtin
	execute_bin(current->token->content, data, arguments);
	exit(0);
}

void	execute_commands(t_command_list *current, t_pipe_fd **pipe_fd, pid_t *process, t_shell_data *data)
{
	int			i;
	int			pipe_n;
	t_pipe_fd *in_pipe;
	t_pipe_fd *out_pipe;

	i = 0;
	pipe_n = count_symbols(D_PIPE, current);
	in_pipe = NULL;
	while (current)
	{
		if (i < pipe_n && pipe_fd)
			out_pipe = pipe_fd[i];
		else
			out_pipe = NULL;
		if (current->symbol == CMD)
		{
			process[i] = fork();
			if (process[i] == 0)
				execute_cmd(current, data, in_pipe, out_pipe);
			i++;
			close_pipe(in_pipe);
		}
		if (out_pipe)
			in_pipe = out_pipe;
		current = current->next;
	}
	//int j = 0;
	i--;
	while (i >= 0)
	{
		printf("waiting for: %d\n", process[i]);
		int k = waitpid(process[i], NULL, 0);
		printf("finished: %d\n", k);
		i--;
	}
}
