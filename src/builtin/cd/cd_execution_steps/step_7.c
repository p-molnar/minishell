/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_7.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:08:59 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/04 15:56:33 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>

/*
7. If the -P option is in effect, proceed to step 10. If curpath
	does not begin with a <slash> character, set curpath to the
	string formed by the concatenation of the value of PWD, a
	<slash> character if the value of PWD did not end with a
	<slash> character, and curpath.
*/

#include <stdio.h>

void	exec_step_7(char **curpath, t_var **env_var, int *step)
{
	if (curpath && *curpath && *curpath[0] != '/')
		*curpath = path_concat(env_var[PWD]->val, *curpath);
	*step += 1;
}
