/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:00:42 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/30 13:02:31 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	open_redirect_infile(t_command_list *current, int *fd)
{
	close(*fd);
	*fd = open(current->token->content, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Could not open file ", STDERR_FILENO);
		ft_putendl_fd(current->token->content, STDERR_FILENO);
		return (1);
	}
	dup2(*fd, STDIN_FILENO);
	return (0);
}

int	open_redirect_outfile(t_command_list *current, int *fd)
{
	close(*fd);
	if (current->symbol == OUTFILE)
		*fd = open(current->token->content, O_RDWR | O_CREAT, 0644);
	else
		*fd = open(current->token->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		ft_putstr_fd("Could not open file ", STDERR_FILENO);
		ft_putendl_fd(current->token->content, STDERR_FILENO);
		return (1);
	}
	dup2(*fd, STDOUT_FILENO);
	return (0);
}

int	redirect_files(t_command_list *current, int og_stdin,
						int *fd_in, int *fd_out, t_shell_data *data)
{
	int		ret;

	ret = 0;
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == OUTFILE || current->symbol == OUTFILE_APP)
			ret = open_redirect_outfile(current, fd_out);
		if (current->symbol == INFILE)
			ret = open_redirect_infile(current, fd_in);
		if (current->symbol == HEREDOC_DELIMITER)
			open_heredoc(current->token->content, og_stdin, data);
		current = current->next;
	}
	return (ret);
}

void	redirect_pipes(t_pipe_fd *in_pipe, t_pipe_fd *out_pipe)
{
	if (in_pipe)
	{
		dup2(in_pipe->pipe_end[0], STDIN_FILENO);
		close(in_pipe->pipe_end[1]);
	}
	if (out_pipe)
	{
		dup2(out_pipe->pipe_end[1], STDOUT_FILENO);
		close(out_pipe->pipe_end[0]);
	}
}
