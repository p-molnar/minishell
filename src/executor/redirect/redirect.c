/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:00:42 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/23 18:13:08 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	open_redirect_infile(t_command_list *current)
{
	static int	fd;

	close(fd);
	fd = open(current->token->content, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Could not open file ", 2);
		ft_putendl_fd(current->token->content, 2);
		return (1);
	}
	dup2(fd, 0);
	return (0);
}

int	open_redirect_outfile(t_command_list *current)
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
		return (1);
	}
	dup2(fd, 1);
	return (0);
}

int	redirect_files(t_command_list *current, int og_stdin)
{
	int		ret;

	ret = 0;
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == OUTFILE || current->symbol == OUTFILE_APP)
			ret = open_redirect_outfile(current);
		if (current->symbol == INFILE)
			ret = open_redirect_infile(current);
		if (current->symbol == HEREDOC_DELIMITER)
			open_heredoc(current->token->content, og_stdin);
		current = current->next;
	}
	return (ret);
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
