/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 13:28:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/20 14:12:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>

int	exec_step_1(t_var **env_var, char **dir, t_shell_data *data)
{
	if (env_var[HOME] == NULL
		|| *env_var[HOME]->val == '\0'
		|| *env_var[HOME]->val == NULL)
	{
		return (1);
	}
	dir = env_var[HOME]->val;
	return (0);
}
