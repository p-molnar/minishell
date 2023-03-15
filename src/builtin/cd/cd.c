/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 15:10:22 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 11:22:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd(char *dir, t_shell_data *data)
{
	t_var	*home_env_var;
	t_var	*cdpath_env_var;
	t_var	*var;
	char	*home_val;

	home_env_var = get_var_by_name("HOME", data->env_vars);
	cdpath_env_var = get_var_by_name("CDPATH", data->env_vars);
	if (!dir || *dir == '\0')
	{
		if (home_env_var == NULL || home_env_var->val == '\0')
			return ;
		home_val = home_env_var->val;
		cd (home_val, data);

	}
	else if (*dir == '/')
	{
		var = get_var_by_name("PWD", data->env_vars);
		if (var)
			var->val = dir;
	}

	// 	if (!tmp)
	// 		return ;
	// 	// free tmp somehow!
	// 	tmp = ft_strjoin(tmp, "/");
	// 	tmp = ft_strjoin(tmp, dir);
	// 	cd(tmp, data);
	// }
}

