/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:38:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 10:38:58 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ms_data_types.h>
# include <ms_macros.h>
# include <termios.h>

# define PROMPT_MSG "minishell$ "

//  readline
void			rl_replace_line(const char *text, int clear_undo);

//	free_objects.c
void			free_var_list(t_list *var_list);
void			free_token_list(t_token_list *list);
void			free_list(t_list *list);

//	character_reader.c
char			*read_prompt(const char *prompt);

//	tokenizer.c
t_token_list	*tokenizer(const char *prompt);

//	token_list_util.c
t_token_list	*new_node(char *content, int token_type);
void			add_node_last(t_token_list **list, t_token_list *node);
void			iter_tokens(t_token_list *l, int fd, void (*f)(char *, int));

//	list_util.c
t_list			*get_node(void *lookup_content, t_list *list);

//	token_classifier.c
void			classify_tokens(t_token_list *list);

//	parse_commands
t_command_list	*parse_commands(t_token_list *token);
int				parse_operator(t_command_list **cmd_list, t_token_list *token);

//	command_list_util.c
void			copy_token(t_token_list **copy, t_token_list *original);
t_command_list	*new_command_node(int symbol, t_token_list *phrase);
void			add_command_back(t_command_list **list, t_command_list *node);
void			free_command_list(t_command_list *list);

//	expander.c
void			expand_tokens(t_shell_data *data);

//	expander_util.c
char			*parse_var_name(char *s);
char			*chardup(char *s);
char			*list_to_str(t_list *l);

//  signal_handler.c
void			setup_signal_handler(t_shell_data *data);
void			handle_int_signal(int signum);

//	variable_interpreter.c
void			parse_shell_variable(t_shell_data *data);
void			parse_env_variable(char **env, t_list **list);

//	variable_parser_util.c
t_var			*parse_var(char *s);
int				is_valid_var_definition(char *s);
t_var			*get_var(char *lookup_name, t_list *list);

//	executor
void			executor(t_shell_data *data, t_command_list *commands);
void			execute_commands(t_command_list *current, t_pipe_fd *pipe_fd,
					pid_t *process, t_shell_data *data);
int				check_parent_builtin(t_command_list *current,
					t_shell_data *data);
void			execute_builtin(char *cmd, t_shell_data *data, char **args);
int				count_symbols(int symbol, t_command_list *current);
int				count_symbols_simple_cmd(int symbol, t_command_list *current);
char			**compound_args(t_command_list *current);
char			**path_builder(t_shell_data *data);
void			close_pipe(t_pipe_fd *pipe);
void			add_var(t_var *new_var, t_list **list);

//	redirect.c
int				redirect_files(t_command_list *current, int og_stdin,
					int *fd_in, int *fd_out);
void			redirect_pipes(t_pipe_fd *in_pipe, t_pipe_fd *out_pipe);
void			open_heredoc(char *delimiter, int og_stdin);

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
void			echo(char **args);

//	exit.c
void			builtin_exit(char **args);

//	CD
//	cd.c
int				cd(char *dir, t_shell_data *data);
int				exec_step_1_2(t_var **env_var, char **dir, int *step);
void			exec_step_3(char *dir, char **curpath, int *step);
void			exec_step_4(char *dir, int *step);
void			exec_step_5(char *dir, char **curpath, t_var **var, int *step);
void			exec_step_6(char *dir, char **curpath, int *step);
void			exec_step_7(char **curpath, t_var **env_var, int *step);
int				exec_step_8(char **curpath, int *step);

//	update_working_dirs.c
int				update_wdirs(char *dir, t_var *var[ENV_SIZE],
					t_shell_data *data);

//	cd_utils.c
int				get_arr_size(void **arr);
char			*path_concat(char *basepath, char *relpath);
void			free_arr(void **arr);
void			free_var_obj(t_var *var);
char			*n_arr_to_str(char **arr, char *c, int n);

#endif
