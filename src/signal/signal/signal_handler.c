/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 14:42:26 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/11 17:15:59 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>

void	handle_int_signal(int signum)
{
	signal(SIGINT, handle_int_signal);
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	setup_signal_handler(t_shell_data *data)
{
	struct termios	my_termios;

	signal(SIGINT, handle_int_signal);
	signal(SIGQUIT, SIG_IGN);
	my_termios = data->original_termios;
	my_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &my_termios);
}
