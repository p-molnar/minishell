/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 17:50:14 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/21 13:00:34 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

void	open_heredoc(char *delimiter, int og_stdin)
{
	int		here_pipe[2];
	int		d_len;
	char	*buf;

	d_len = ft_strlen(delimiter);
	buf = NULL;
	pipe(here_pipe);
	dup2(og_stdin, 0);
	signal(SIGINT, handle_int_signal_heredoc);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, delimiter, d_len + 1))
	{
		ft_putendl_fd(buf, here_pipe[1]);
		free(buf);
		buf = readline("> ");
		//variables in buf should be expanded here
	}
	free(buf);
	dup2(here_pipe[0], 0);
	close(here_pipe[1]);
	signal(SIGINT, handle_int_signal);
}
