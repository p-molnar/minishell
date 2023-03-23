/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 14:48:13 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/23 16:10:34 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	close_pipe(t_pipe_fd *pipe)
{
	if (pipe)
	{
		close(pipe->pipe_end[0]);
		close(pipe->pipe_end[1]);
	}
}

t_pipe_fd	*setup_pipes(int pipe_n)
{
	t_pipe_fd	*pipe_fd;
	int			i;

	i = 0;
	if (pipe_n <= 0)
		return (NULL);
	pipe_fd = malloc(sizeof(t_pipe_fd) * pipe_n);
	while (i < pipe_n)
	{
		pipe(pipe_fd[i].pipe_end);
		i++;
	}
	return (pipe_fd);
}

void	executor(t_shell_data *data, t_command_list *commands)
{
	int			pipe_n;
	int			ret;
	t_pipe_fd	*pipe_fd;
	pid_t		*process;

	ret = 0;
	pipe_n = count_symbols(D_PIPE, commands);
	pipe_fd = setup_pipes(pipe_n);
	process = malloc(sizeof(pid_t) * (pipe_n + 1));
	if (pipe_n == 0)
		ret = check_parent_builtin(commands, data);
	if (ret == 0)
		execute_commands(commands, pipe_fd, process, data);
	free(process);
	free(pipe_fd);
}
