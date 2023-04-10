/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_bin.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/10 16:27:43 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/10 16:59:37 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

void	test_path(char *path, char *og_path)
{
	struct stat	path_stat;
	int			err_code;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		error(strconcat(2, og_path, ": is a directory"), EXIT, 126);
	else
	{
		err_code = access(path, F_OK);
		if (err_code != 0)
			error(strconcat(3, og_path, ": ", strerror(errno)), EXIT, 127);
		err_code = access(path, X_OK);
		if (err_code != 0)
			error(strconcat(3, og_path, ": ", strerror(errno)), EXIT, 126);
	}
}

void	set_up_env_vars(t_var **env_vars, t_list *var_list)
{
	env_vars[HOME] = NULL;
	env_vars[OLDPWD] = NULL;
	env_vars[ITERABLE_PATH] = get_var("PATH", var_list, ENV);
	env_vars[PWD] = create_var(ft_strdup("PWD"),
			getcwd(NULL, 0),
			UNDEFINED);
}

void	execute_bin(char *cmd, t_shell_data *data, char	**args)
{
	char		**env_arr;
	char		*bin_path;
	t_var		*default_env_vars[ENV_SIZE];
	t_error		err;

	bin_path = NULL;
	set_up_env_vars(default_env_vars, data->variables);
	env_arr = convert_list_to_arr(data->variables, ENV);
	if (cmd && (*cmd == '.' || *cmd == '/'))
		get_abs_path(cmd, &bin_path, default_env_vars, 8);
	else if (cmd && *cmd == '\0')
		exit(0);
	else
	{
		get_abs_path(cmd, &bin_path, default_env_vars, 5);
		if (access(bin_path, F_OK) != 0)
			return ;
	}
	test_path(bin_path, cmd);
	err.code = execve(bin_path, args, env_arr);
	free_obj((void **)&bin_path);
	free_arr((void **)env_arr);
	if (err.code != 0)
		error(strconcat(3, bin_path, ": ", strerror(errno)), EXIT, errno);
}
