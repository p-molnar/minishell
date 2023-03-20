/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 17:50:14 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/20 17:22:22 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

void	open_heredoc(char *delimiter)
{
	int		here_pipe[2];
	int		d_len;
	char	*buf;

	d_len = ft_strlen(delimiter);
	buf = NULL;
	pipe(here_pipe);
	signal(SIGINT, SIG_DFL);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, delimiter, d_len + 1))
	{
		ft_putendl_fd(buf, here_pipe[1]);
		free(buf);
		buf = readline("> ");
	}
	free(buf);
	dup2(here_pipe[0], 0);
	close(here_pipe[1]);
	signal(SIGINT, handle_signal);
}
