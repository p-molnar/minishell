/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:00:42 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/05 16:46:20 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void	initialise_redirection_data(t_redir_data *redir_data)
{
	redir_data->fd_in = -1;
	redir_data->fd_out = -1;
	redir_data->og_stdin = dup(STDIN_FILENO);
	redir_data->heredoc_pipe_out = -1;
}

int	open_redirect_infile(t_command_list *list, t_redir_data *redir_dat)
{
	char	*err_msg;
	char	*err_tkn;

	close(redir_dat->fd_in);
	redir_dat->fd_in = open(list->token->content, O_RDONLY);
	if (redir_dat->fd_in < 0)
	{
		err_tkn = ft_strjoin(list->token->content, ": ");
		err_msg = ft_strjoin(err_tkn, strerror(errno));
		error(err_msg, RETURN, EXIT_FAILURE);
		free(err_msg);
		free(err_tkn);
		return (EXIT_FAILURE);
	}
	dup2(redir_dat->fd_in, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int	open_redirect_outfile(t_command_list *list, t_redir_data *redir_dat)
{
	char	*err_msg;
	char	*err_tkn;

	close(redir_dat->fd_out);
	if (list->symbol == OUTFILE)
		redir_dat->fd_out = open(list->token->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		redir_dat->fd_out = open(list->token->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir_dat->fd_out < 0)
	{
		err_tkn = ft_strjoin(list->token->content, ": ");
		err_msg = ft_strjoin(err_tkn, strerror(errno));
		error(err_msg, RETURN, EXIT_FAILURE);
		free(err_msg);
		free(err_tkn);
		return (EXIT_FAILURE);
	}
	dup2(redir_dat->fd_out, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	redirect_files(t_command_list *current, t_redir_data *redir_dat,
		t_shell_data *data)
{
	int		ret;

	ret = 0;
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == OUTFILE || current->symbol == OUTFILE_APP)
			ret = open_redirect_outfile(current, redir_dat);
		if (current->symbol == INFILE)
			ret = open_redirect_infile(current, redir_dat);
		if (current->symbol == HEREDOC_DELIMITER)
			open_heredoc(current->token->content, redir_dat, data);
		current = current->next;
		if (ret != 0)
			return (ret);
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
