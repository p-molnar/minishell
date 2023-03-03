/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:38:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/03 15:05:10 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ms_data_types.h>
# include <termios.h>

# define PROMPT_MSG "minishell$ "

//  readline
void			rl_replace_line(const char *text, int clear_undo);

//	character_reader.c
char			*read_prompt(const char *prompt);

//	tokenizer.c
t_token_list	*tokenizer(const char *prompt);

//	token_list_util.c
t_token_list	*new_node(char *content, int token_type);
void			add_node_last(t_token_list **list, t_token_list *node);
void			free_list(t_token_list *list);

//	token_classifier.c
void			classify_tokens(t_token_list *list);

//	parse_commands.c
t_command_list	*parse_commands(t_token_list *token);

//	command_list_util.c
void			copy_token(t_token_list **copy, t_token_list *original);
void			copy_phrase(t_token_list **copy, t_token_list *original);
t_command_list	*new_command_node(int symbol, t_token_list *phrase);
void			add_command_back(t_command_list **list, t_command_list *node);
void			free_command_list(t_command_list *list);

//  signal_handler.c
void			setup_signal_handler(struct termios *original_termios);
void			handle_signal(int signum);

#endif
