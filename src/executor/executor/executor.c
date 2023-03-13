/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 14:48:13 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/13 16:32:25 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>

void	close_pipes(t_pipe_fd **pipe_fd, int pipe_n)
{
	while (pipe_n > 0)
	{
		close(pipe_fd[pipe_n - 1]->pipe_end[0]);
		close(pipe_fd[pipe_n - 1]->pipe_end[1]);
		pipe_n--;
	}
	free(pipe_fd);
}

t_pipe_fd	**setup_pipes(int pipe_n)
{
	t_pipe_fd	**pipe_fd;
	int			i;

	i = 0;
	pipe_fd = malloc(sizeof(t_pipe_fd *) * pipe_n);
	while (i < pipe_n)
	{
		pipe(pipe_fd[i]->pipe_end);
		i++;
	}
	return (pipe_fd);
}

int		count_symbols(int symbol, t_command_list *current)
{
	int		count;

	count = 0;
	while (current)
	{
		if (current->symbol == symbol)
			count++;
		current = current->next;
	}
	return (count);
}

void	executor(t_shell_data *data, t_command_list *commands)
{
	int		cmd_n;
	int		**pipe_fd;
	pid_t	*process;

	cmd_n = count_symbols(CMD, commands);
	pipe_fd = setup_pipes(cmd_n - 1);
	process = malloc(sizeof(pid_t) * cmd_n);
	execute_commands(*commands, pipe_fd, process, data);
	free(process);
	close_pipes(pipe_fd, cmd_n - 1);
}
