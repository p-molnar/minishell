/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/31 13:38:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/10 16:17:16 by jzaremba      ########   odam.nl         */
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
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		free_obj((void **)&msg);
	}
	if (exit_method == EXIT)
		exit(value);
	else if (exit_method == RETURN)
	{
		g_exit_status = value << 8;
		return (value);
	}
	return (EXIT_FAILURE);
}
