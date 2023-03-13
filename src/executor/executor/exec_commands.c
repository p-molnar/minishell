/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:34:30 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/13 18:25:01 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft/inc/libft.h>

char	**path_builder(void)
{
	char	**path;
	char	*finalpath;
	int		i;

	i = 0;
	//getenv should be replaced with our own function
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		finalpath = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = finalpath;
		i++;
	}
	return (path);
}

void	execute_bin(char *command, t_shell_data *data)
{
	char	**argument;
	char	**path;
	char	*commandpath;
	int		i;

	//handle arguments in earlier function and pass along, not here
	argument = ft_split(command, ' ');
	path = path_builder();
	i = 0;
	while (path[i])
	{
		commandpath = ft_strjoin(path[i], argument[0]);
		//env vars should be turned into array of strings
		execve(commandpath, argument, data->env_vars);
		free(commandpath);
		commandpath = NULL;
		i++;
	}
	free(commandpath);
	ft_putstr_fd("Command not found", 2);
	exit();
}

void	execute_cmd(t_command_list *current, t_shell_data *data, t_pipe_fd *in_pipe, t_pipe_fd *out_pipe)
{
	//handle pipe redirects
	//handle file redirects
	//compound the arguments into usable array
	while (current->symbol != CMD)
		current = current->next;
	//check for builtin, execute builtin
	execute_bin(current->token->content, data); //should pass arguments too
}

void	execute_commands(t_command_list *current, t_pipe_fd **pipe_fd, pid_t *process, t_shell_data *data)
{
	int	i;
	t_pipe_fd *in_pipe;
	t_pipe_fd *out_pipe;

	i = 0;
	in_pipe = NULL;
	while (current)
	{
		out_pipe = pipe_fd[i];
		process[i] = fork();
		if (process[i] == 0)
			execute_cmd(current, data, in_pipe, out_pipe);
		else
			i++;
		while (current->symbol != D_PIPE)
			current = current->next;
		in_pipe = pipe_fd[i - 1];
		current = current->next;
	}
	while (i > 0)
	{
		waitpid(process[i], NULL, 0);
		i--;
	}
}