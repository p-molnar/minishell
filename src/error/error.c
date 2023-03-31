/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 13:38:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 13:57:44 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ms_macros.h>
#include <unistd.h>

int	error(char *msg, int exit_method, int value)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	if (exit_method == EXIT)
		exit(value);
	else if (exit_method == RETURN)
		return (value);
	return (0);
}
