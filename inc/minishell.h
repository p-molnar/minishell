/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:38:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/14 14:46:11 by pmolnar       ########   odam.nl         */
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
t_token_list	*new_node(char *content, char *tkn_start, int token_type);
void			add_node_last(t_token_list **list, t_token_list *node);
void			free_list(t_token_list *list);

//	token_classifier.c
void			classify_tokens(t_token_list *list);

//	parse_commands.c
t_command_list	*parse_commands(t_token_list *token);
int				parse_operator(t_command_list **command_list, t_token_list *token);

//	command_list_util.c
void			copy_token(t_token_list **copy, t_token_list *original);
t_command_list	*new_command_node(int symbol, t_token_list *phrase);
void			add_command_back(t_command_list **list, t_command_list *node);
void			free_command_list(t_command_list *list);

//	expander.c
void			expand_tokens(t_shell_data *data);

//	expander_util.c
int				count_var(char *s);
char			*find_replace(char *needle, char *nail, char *haystack);

//  signal_handler.c
void			setup_signal_handler(struct termios *original_termios);
void			handle_signal(int signum);

//	variable_interpreter.c
void			parse_shell_variable(t_shell_data *data);
void			parse_env_variable(char **env, t_list **list);

//	variable_parser_util.c
void			parse_var(char *s, t_var *var);
int				is_valid_var_definition(char *s);
t_list			*find_var_by_name(char *lookup_name, t_list *list);
void			add_var(t_var *new_var, t_list **list);

//	BUILTINS

//	export.c
void			export(t_token_list *token, t_shell_data *data);

//	env.c
void			env(t_list *var_list);

//	unset.c
void			unset(char *var_name, t_shell_data *data);

//	pwd.c
void			pwd(t_shell_data *data);

//	echo.c
void			echo(char *flag, char *s);
#endif
