/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:16:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/21 12:07:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
3. If the directory operand begins with a <slash> character, set
curpath to the operand and proceed to step 7.
*/

void	exec_step_3(char *dir, char **curpath, int *step)
{
	if (dir[0] == '/')
	{
		*curpath = dir;
		*step = 7;
	}
	else
		*step += 1;
}
