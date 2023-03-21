/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_6.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 14:57:15 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/21 15:03:11 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
6. Set curpath to the directory operand.
*/

void	exec_step_6(char *dir, char **curpath, int *step)
{
	if (curpath && dir)
		*curpath = dir;
	*step += 1;
}
