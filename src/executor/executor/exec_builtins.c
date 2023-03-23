/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtins.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 13:47:18 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/23 14:26:19 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>

void	execute_builtin(char *cmd, t_shell_data *data, char **args)
{
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		exit (0);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
	{
		env(data->env_vars);
		exit (0);
	}
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
	{
		pwd(data);
		exit (0);
	}
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
	{
		echo(args);
		exit (0);
	}
}
