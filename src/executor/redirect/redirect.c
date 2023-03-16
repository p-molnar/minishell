/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:00:42 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/16 17:49:49 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	open_redirect_infile(t_command_list *current)
{
	static int	fd;

	close(fd);
	fd = open(current->token->content, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Could not open file ", 2);
		ft_putendl_fd(current->token->content, 2);
		exit(0);
	}
	dup2(fd, 0);
}

void	open_redirect_outfile(t_command_list *current)
{
	static int	fd;

	close(fd);
	if (current->symbol == OUTFILE)
		fd = open(current->token->content, O_RDWR | O_CREAT, 0644);
	else
		fd = open(current->token->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Could not open file ", 2);
		ft_putendl_fd(current->token->content, 2);
		exit(0);
	}
	dup2(fd, 1);
}

void	redirect_files(t_command_list *current)
{
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == OUTFILE || current->symbol == OUTFILE_APP)
			open_redirect_outfile(current);
		if (current->symbol == INFILE)
			open_redirect_infile(current);
		// if (current->symbol == HEREDOC_DELIMITER)
		// 	open_heredoc(current->token->content);
		current = current->next;
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
