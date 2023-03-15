/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_working_dirs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 14:21:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 15:19:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>

void	update_oldpwd(t_var	**var, t_shell_data *data)
{
	t_var	*new_var;

	var[OLDPWD] = get_var("OLDPWD", data->env_vars);
	if (!var[OLDPWD])
	{
		new_var = ft_calloc(1, sizeof(t_var));
		if (!new_var)
			return ;
		new_var->name = "OLDPWD"; // read only issue with free
		new_var->val = var[PWD]->val;
		add_var(new_var, &data->env_vars);
	}
	else
	{
		free(var[OLDPWD]->val);
		var[OLDPWD]->val = var[PWD]->val;
	}
}

void	update_pwd(char *dir, t_var **var)
{
	free(var[PWD]->val);
	var[PWD]->val = dir;
}

void	update_wdirs(char *dir, t_var **var, t_shell_data *data)
{
	update_oldpwd(var, data);
	update_pwd(dir, var);
}
