/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 13:55:12 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/03 13:41:18 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (arg[i] == '-' || arg[i] == '+')
		return (0);
	return (1);
}

int	builtin_exit(char **args)
{
	if (!args)
		exit(0);
	if (args[1])
	{
		if (!is_number(args[1]))
			error("numeric argument required", EXIT, 255);
		if (args[2])
			return (error("too many arguments", RETURN, 1));
		exit(ft_atoi(args[1]));
	}
	exit(0);
	return (EXIT_SUCCESS);
}
