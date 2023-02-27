/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:38:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/27 15:46:32 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>

# define PROMPT_MSG "minishell$ "

char	*read_prompt(const char *prompt);
void	setup_signal_handler(struct termios *original_termios);
void	handle_signal(int signum);
void	rl_replace_line(const char *text, int clear_undo);

#endif