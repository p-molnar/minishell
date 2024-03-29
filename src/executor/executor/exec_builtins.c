/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 13:47:18 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/07 13:21:00 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

void	execute_builtin(char *cmd, t_shell_data *data, char **args)
{
	if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		exit (builtin_export(args, data));
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		exit (builtin_cd(args, data));
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		exit (builtin_exit(args));
	else if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		exit (builtin_env(data->variables));
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		exit (builtin_pwd());
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		exit (builtin_echo(args));
}

void	execute_parent_builtin(t_command_list *current, t_shell_data *data)
{
	t_token_list	*cmd;
	char			**args;

	args = NULL;
	cmd = get_next_command(current);
	if (!cmd)
		return ;
	args = compound_args(current);
	if (ft_strncmp(cmd->content, "export", ft_strlen("export") + 1) == 0)
		builtin_export(args, data);
	else if (ft_strncmp(cmd->content, "unset", ft_strlen("unset") + 1) == 0)
		builtin_unset(args, data);
	else if (ft_strncmp(cmd->content, "cd", ft_strlen("cd") + 1) == 0)
		builtin_cd(args, data);
	else if (ft_strncmp(cmd->content, "exit", ft_strlen("exit") + 1) == 0)
		builtin_exit(args);
	free(args);
}

void	close_redirection_data(t_redir_data *redir_data)
{
	if (redir_data->fd_in >= 0)
		close(redir_data->fd_in);
	if (redir_data->fd_out >= 0)
		close(redir_data->fd_out);
	if (redir_data->og_stdin >= 0)
		close(redir_data->og_stdin);
	if (redir_data->heredoc_pipe_out >= 0)
		close(redir_data->heredoc_pipe_out);
}

int	prepare_parent_builtin(t_command_list *current, t_shell_data *data)
{
	int				original_stdout;
	t_redir_data	redir_data;

	initialise_redirection_data(&redir_data);
	original_stdout = dup(STDOUT_FILENO);
	signal(SIGINT, SIG_DFL);
	tcsetattr(0, 0, &data->original_termios);
	if (redirect_files(current, &redir_data, data))
		return (1);
	execute_parent_builtin(current, data);
	dup2(redir_data.og_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close_redirection_data(&redir_data);
	close(original_stdout);
	return (1);
}

int	check_parent_builtin(t_command_list *current, t_shell_data *data)
{
	t_token_list	*cmd;

	if (!current)
		return (0);
	cmd = get_next_command(current);
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd->content, "export", ft_strlen("export") + 1) == 0)
		return (prepare_parent_builtin(current, data));
	else if (ft_strncmp(cmd->content, "unset", ft_strlen("unset") + 1) == 0)
		return (prepare_parent_builtin(current, data));
	else if (ft_strncmp(cmd->content, "cd", ft_strlen("cd") + 1) == 0)
		return (prepare_parent_builtin(current, data));
	else if (ft_strncmp(cmd->content, "exit", ft_strlen("exit") + 1) == 0)
		return (prepare_parent_builtin(current, data));
	return (0);
}
