/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 17:50:14 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/27 17:11:25 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

void	open_heredoc(char *delimiter, int og_stdin)
{
	int		here_pipe[2];
	int		d_len;
	char	*buf;

	d_len = ft_strlen(delimiter);
	buf = NULL;
	pipe(here_pipe);
	dup2(og_stdin, STDIN_FILENO);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, delimiter, d_len + 1))
	{
		//variables in buf should be expanded here
		ft_putendl_fd(buf, here_pipe[1]);
		free(buf);
		buf = readline("> ");
	}
	free(buf);
	dup2(here_pipe[0], STDIN_FILENO);
	close(here_pipe[1]);
}
