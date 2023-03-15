/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 15:10:22 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 14:47:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>

void	cd(char *dir, t_shell_data *data)
{
	t_var	*var[SIZE];

	if (!dir || *dir == '\0')
	{
		var[HOME] = get_var("HOME", data->env_vars);
		if (var[HOME] == NULL || var[HOME]->val == '\0')
			return ;
		cd (var[HOME]->val, data);
	}
	else if (*dir == '/')
	{
		var[PWD] = get_var("PWD", data->env_vars);
		if (var[PWD])
			update_wdirs(ft_strdup(dir), var, data);
	}
}

