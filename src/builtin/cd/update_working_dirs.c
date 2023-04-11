/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_working_dirs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 14:21:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/11 11:23:30 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	update_oldpwd(t_var	**var, t_shell_data *data)
{
	t_var		*new_var;

	if (!var[OLDPWD] && !data->oldpwd_set)
	{
		new_var = create_var(
				ft_strdup("OLDPWD"),
				ft_strdup(var[PWD]->val),
				SHL | ENV
				);
		add_var(new_var, &data->variables);
	}
	else
	{
		data->oldpwd_set = 1;
		if (var[OLDPWD])
			free(var[OLDPWD]->val);
		if (var[OLDPWD])
			var[OLDPWD]->val = ft_strdup(var[PWD]->val);
	}
}

void	update_pwd(char *dir, t_shell_data *data)
{
	t_var	*pwd;

	pwd = get_var("PWD", data->variables, ENV);
	if (pwd)
	{
		free(pwd->val);
		pwd->val = ft_strdup(dir);
	}
}

int	update_wdirs(char *dir, char *og_dir,
		t_var **var, t_shell_data *data)
{
	char	*err_msg;
	int		err_code;
	int		ret_val;

	err_msg = NULL;
	err_code = chdir(dir);
	if (err_code == 0)
	{
		update_oldpwd(var, data);
		update_pwd(dir, data);
		return (EXIT_SUCCESS);
	}
	else
	{
		err_msg = strconcat(3, strerror(errno), ": ", og_dir);
		ret_val = error(err_msg, RETURN, 1);
		return (ret_val);
	}
}
