/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 15:10:22 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/22 11:42:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>

static void	init_env_vars(t_var **env_var, t_shell_data *data)
{
	env_var[HOME] = get_var("HOME", data->env_vars);
	env_var[PWD] = get_var("PWD", data->env_vars);
	env_var[OLDPWD] = get_var("OLDPWD", data->env_vars);
	env_var[CDPATH] = get_var("CDPATH", data->env_vars);
}

// Below 8 steps follow the man page
// https://man7.org/linux/man-pages/man1/cd.1p.html
static int	exec_steps(char *dir, char **curpath, t_var **env_var)
{
	int		step;

	step = 1;
	if (step == 1)
	{
		if (exec_step_1_2(env_var, &dir, &step))
			return (1);
	}
	if (step == 3)
		exec_step_3(dir, curpath, &step);
	if (step == 4)
		exec_step_4(dir, &step);
	if (step == 5)
		exec_step_5(dir, curpath, env_var, &step);
	if (step == 6)
		exec_step_6(dir, curpath, &step);
	if (step == 7)
		exec_step_7(curpath, env_var, &step);
	if (step == 8)
		exec_step_8(curpath, &step);
	return (0);
}

int	cd(char *dir, t_shell_data *data)
{
	t_var	*env_var[ENV_SIZE];
	char	*curpath;

	curpath = NULL;
	init_env_vars(env_var, data);
	if (exec_steps(dir, &curpath, env_var))
		return (1);
	return (update_wdirs(curpath, env_var, data));
}

