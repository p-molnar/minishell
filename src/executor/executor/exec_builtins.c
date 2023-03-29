/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 13:47:18 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/29 15:56:14 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

void	execute_builtin(char *cmd, t_shell_data *data, char **args)
{
	if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
	{
		builtin_exit (args);
		exit (1);
	}
	else if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
	{
		env(data->env_vars);
		exit (0);
	}
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
	{
		pwd(data);
		exit (0);
	}
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
	{
		echo(args);
		exit (0);
	}
}

void	execute_parent_builtin(t_command_list *current, t_shell_data *data)
{
	t_token_list	*cmd;
	t_token_list	*arg;
	char			*arg_content;

	arg_content = NULL;
	cmd = get_next_command(current);
	if (!cmd)
		return ;
	arg = get_next_argument(current);
	if (arg)
		arg_content = arg->content;
	if (ft_strncmp(cmd->content, "export", ft_strlen("export") + 1) == 0)
		export(arg, data);
	else if (ft_strncmp(cmd->content, "unset", ft_strlen("unset") + 1) == 0)
		unset(arg->content, data);
	else if (ft_strncmp(cmd->content, "cd", ft_strlen("cd") + 1) == 0)
		cd(arg->content, data);
	else if (ft_strncmp(cmd->content, "exit", ft_strlen("exit") + 1) == 0)
		builtin_exit(compound_args(current));
}

int	prepare_parent_builtin(t_command_list *current, t_shell_data *data)
{
	int				original_stdin;
	int				original_stdout;
	int				fd_in;
	int				fd_out;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	fd_in = -1;
	fd_out = -1;
	signal(SIGINT, SIG_DFL);
	tcsetattr(0, 0, &data->original_termios);
	if (redirect_files(current, original_stdin, &fd_in, &fd_out))
		return (1);
	execute_parent_builtin(current, data);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	close(original_stdin);
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
