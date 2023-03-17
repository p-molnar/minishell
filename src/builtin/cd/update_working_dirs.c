/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_working_dirs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 14:21:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/17 10:06:58 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

void	update_oldpwd(t_var	*var[ENV_SIZE], t_shell_data *data)
{
	t_var	*new_var;

	if (!var[OLDPWD])
	{
		// printf("oldpwd not exists\n");
		new_var = ft_calloc(1, sizeof(t_var));
		if (!new_var)
			return ;
		new_var->name = ft_strdup("OLDPWD"); // check for null
		new_var->val = ft_strdup(var[PWD]->val);
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
	var[PWD]->val = dir;
}

void	update_wdirs(char *dir, t_var *var[ENV_SIZE], t_shell_data *data)
{
	update_oldpwd(var, data);
	update_pwd(dir, var);
}
