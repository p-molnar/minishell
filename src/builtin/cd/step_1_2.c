/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_1_2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 13:28:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/21 11:05:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>

/*
	1. If no directory operand is given and the HOME environment
	variable is empty or undefined, the default behavior is
	implementation-defined and no further steps shall be taken.

	2. If no directory operand is given and the HOME environment
	variable is set to a non-empty value, the cd utility shall
	behave as if the directory named in the HOME environment
	variable was specified as the directory operand.
*/


int	exec_step_1_2(t_var **env_var, char **dir, int *step)
{
	if (*dir == NULL)
	{
		if (env_var[HOME] == NULL
			|| env_var[HOME]->val[0] == '\0'
			|| env_var[HOME]->val == NULL)
		{
			return (1);
		}
		else
			*dir = env_var[HOME]->val;
	}
	*step += 2;
	return (0);
}
