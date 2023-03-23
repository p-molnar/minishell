/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 13:47:18 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/23 16:36:04 by jzaremba      ########   odam.nl         */
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
		exit (0);
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

int		execute_parent_builtin(t_command_list *current, t_shell_data *data)
{
	int		original_stdin;
	char	*cmd;
	char	*arg;

	arg = NULL;
	original_stdin = dup(0);
	signal(SIGINT, SIG_DFL);
	tcsetattr(0, 0, &data->original_termios);
	if (redirect_files(current, original_stdin))
		return (1);
	while (current)
	{
		if (current->symbol == CMD)
			break ;
		current = current->next;
	}
	cmd = current->token->content;
	if (current->next)
		arg = current->next->token->content;
	//should make sure arg isn't set to non-arguments in command list
	if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		export(current->token->next, data);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		unset(arg, data);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		cd(arg, data);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		exit (0);
	return (1);
}

int		check_parent_builtin(t_command_list *current, t_shell_data *data)
{
	char			*cmd;
	t_command_list	*start;

	start = current;
	while (current)
	{
		if (current->symbol == CMD)
			break ;
		current = current->next;
	}
	if (!current)
		return (0);
	cmd = current->token->content;
	if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		return (execute_parent_builtin(current, data));
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		return (execute_parent_builtin(current, data));
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (execute_parent_builtin(current, data));
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		return (execute_parent_builtin(current, data));
	return (0);
}
