/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 13:55:12 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/28 15:58:40 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

void	builtin_exit(char **args)
{
	int	i;

	i = 0;
	if (!args)
		exit(0);
	if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_putendl_fd("numeric argument required", STDERR_FILENO);
				exit(255);
			}
			i++;
		}
		if (args[2])
		{
			ft_putendl_fd("too many arguments", STDERR_FILENO);
			return ;
		}
		exit(ft_atoi(args[1]));
	}
	exit(0);
}
