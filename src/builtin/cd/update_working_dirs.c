/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_working_dirs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 14:21:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/02 21:54:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	update_oldpwd(t_var	*var[ENV_SIZE], t_shell_data *data)
{
	t_var	*new_var;

	if (!var[OLDPWD])
	{
		new_var = create_var(ft_strdup("OLDPWD"), ft_strdup(var[PWD]->val));
		add_var(new_var, &data->env_vars);
	}
	else
	{
		free(var[OLDPWD]->val);
		var[OLDPWD]->val = ft_strdup(var[PWD]->val);
	}
}

void	update_pwd(char *dir, t_var *var[ENV_SIZE])
{
	free(var[PWD]->val);
	var[PWD]->val = ft_strdup(dir);
}

int	update_wdirs(char *dir, t_var *var[ENV_SIZE], t_shell_data *data)
{
	if (chdir(dir) != -1)
	{
		update_oldpwd(var, data);
		update_pwd(dir, var);
		return (0);
	}
	else
		return (error(strerror(errno), RETURN, 1));
}
