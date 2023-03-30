/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 17:50:14 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/30 14:00:55 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

char	*replace_variables(char *s, t_shell_data *data)
{
	t_list	*str_list;
	char	*expanded_s;

	str_list = NULL;
	while (s && *s != '\0')
	{
		if (*s == DOLLAR)
			add_variable(&str_list, &s, data);
		else
			ft_lstadd_back(&str_list, ft_lstnew(chardup(s)));
		s++;
	}
	expanded_s = list_to_str(str_list);
	free_list(str_list);
	return (expanded_s);
}

void	open_heredoc(char *delimiter, t_redir_data *redir_dat,
			t_shell_data *data)
{
	int				here_pipe[2];
	int				d_len;
	char			*buf;

	d_len = ft_strlen(delimiter);
	buf = NULL;
	pipe(here_pipe);
	dup2(redir_dat->og_stdin, STDIN_FILENO);
	buf = readline("> ");
	while (buf && ft_strncmp(buf, delimiter, d_len + 1))
	{
		buf = replace_variables(buf, data);
		ft_putendl_fd(buf, here_pipe[1]);
		free(buf);
		buf = readline("> ");
	}
	free(buf);
	dup2(here_pipe[0], STDIN_FILENO);
	close(here_pipe[1]);
}
