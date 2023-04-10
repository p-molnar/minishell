/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_working_dirs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/15 14:21:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/10 11:43:09 by pmolnar       ########   odam.nl         */
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
		new_var = create_var(
				ft_strdup("OLDPWD"),
				ft_strdup(var[PWD]->val),
				SHL | ENV
				);
		add_var(new_var, &data->variables);
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

int	update_wdirs(char *dir, char *og_dir,
		t_var *var[ENV_SIZE], t_shell_data *data)
{
	char	*err_msg;
	int		err_code;
	int		ret_val;

	err_msg = NULL;
	err_code = chdir(dir);
	if (err_code == 0)
	{
		update_oldpwd(var, data);
		update_pwd(dir, var);
		return (EXIT_SUCCESS);
	}
	else
	{
		err_msg = strconcat(3, og_dir, " ", strerror(errno));
		ret_val = error(err_msg, RETURN, err_code);
		free_obj((void **)&err_msg);
		return (ret_val);
	}
}
