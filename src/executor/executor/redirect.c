/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:00:42 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/15 12:45:31 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>
#include <stdio.h>

void	close_pipe(t_pipe_fd *pipe)
{
	if (pipe)
	{
		close(pipe->pipe_end[0]);
		close(pipe->pipe_end[1]);
	}
}

void	redirect_pipes(t_pipe_fd *in_pipe, t_pipe_fd *out_pipe)
{
	if (in_pipe)
	{
		dup2(in_pipe->pipe_end[0], 0);
		close(in_pipe->pipe_end[1]);
	}
	if (out_pipe)
	{
		dup2(out_pipe->pipe_end[1], 1);
		close(out_pipe->pipe_end[0]);
	}
}
