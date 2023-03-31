/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 13:38:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 15:32:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ms_macros.h>
#include <minishell.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	error(char *msg, int exit_method, int value)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (exit_method == EXIT)
		exit(value);
	else if (exit_method == RETURN)
	{
		g_exit_status = value << 8;
		return (value);
	}
	return (0);
}
