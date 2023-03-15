/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 14:48:13 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/15 16:15:06 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	close_free_pipes(t_pipe_fd **pipe_fd, int pipe_n)
{
	if (pipe_fd)
	{
		while (pipe_n > 0)
		{
			close(pipe_fd[pipe_n - 1]->pipe_end[0]);
			close(pipe_fd[pipe_n - 1]->pipe_end[1]);
			free(pipe_fd[pipe_n - 1]);
			pipe_n--;
		}
		free(pipe_fd);
	}
}

t_pipe_fd	**setup_pipes(int pipe_n)
{
	t_pipe_fd	**pipe_fd;
	int			i;

	i = 0;
	if (pipe_n == 0)
		return (NULL);
	pipe_fd = malloc(sizeof(t_pipe_fd *) * pipe_n);
	while (i < pipe_n)
	{
		pipe_fd[i] = malloc(sizeof(t_pipe_fd));
		pipe(pipe_fd[i]->pipe_end);
		i++;
	}
	return (pipe_fd);
}

void	executor(t_shell_data *data, t_command_list *commands)
{
	int			cmd_n;
	t_pipe_fd	**pipe_fd;
	pid_t		*process;

	cmd_n = count_symbols(CMD, commands);
	pipe_fd = setup_pipes(cmd_n - 1);
	process = malloc(sizeof(pid_t) * cmd_n);
	execute_commands(commands, pipe_fd, process, data);
	free(process);
	close_free_pipes(pipe_fd, cmd_n - 1);
}
