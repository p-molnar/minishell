/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 10:16:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/21 12:08:11 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
4. If the first component of the directory operand is dot or
dot-dot, proceed to step 6.
*/

void	exec_step_4(char *dir, int *step)
{
	if (dir[0] == '.')
		*step = 6;
	else
		*step += 1;
}
