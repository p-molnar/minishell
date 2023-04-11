/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 15:10:22 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/11 11:18:06 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_env_vars(t_var **env_var, t_list *var_list)
{
	env_var[HOME] = get_var("HOME", var_list, ENV);
	env_var[OLDPWD] = get_var("OLDPWD", var_list, ENV);
	env_var[ITERABLE_PATH] = get_var("CDPATH", var_list, ENV);
	env_var[PWD] = create_var(ft_strdup("PWD"),
			getcwd(NULL, 0),
			UNDEFINED);
}

// Below 8 steps follow the man page
// https://man7.org/linux/man-pages/man1/cd.1p.html
int	get_abs_path(char *dir, char **curpath, t_var **env_var, int stop)
{
	char	*tmp;
	int		step;

	step = 1;
	if (step == 1 && step <= stop && exec_step_1_2(env_var, &dir, &step))
		return (EXIT_FAILURE);
	if (step == 3 && step <= stop)
		exec_step_3(dir, curpath, &step);
	if (step == 4 && step <= stop)
		exec_step_4(dir, &step);
	if (step == 5 && step <= stop)
		exec_step_5(dir, curpath, env_var, &step);
	if (step == 6 && step <= stop)
		exec_step_6(dir, curpath, &step);
	if (step == 7 && step <= stop)
		exec_step_7(curpath, env_var, &step);
	if (step == 8 && step <= stop)
		exec_step_8(curpath, &step);
	if ((dir && dir[ft_strlen(dir) - 1] != '/' && curpath)
		|| ft_strncmp(*curpath, "/", 2) == 0)
		return (EXIT_SUCCESS);
	tmp = *curpath;
	*curpath = strconcat(2, *curpath, "/");
	free_obj((void **)&tmp);
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **args, t_shell_data *data)
{
	t_var	*env_var[ENV_SIZE];
	int		ret;
	char	*curpath;

	curpath = NULL;
	init_env_vars(env_var, data->variables);
	if (get_abs_path(args[1], &curpath, env_var, 8))
		return (EXIT_FAILURE);
	ret = update_wdirs(curpath, args[1], env_var, data);
	free (curpath);
	free_var(&env_var[PWD]);
	return (ret);
}
