/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 13:55:12 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/11 10:20:47 by pmolnar       ########   odam.nl         */
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
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || (arg[i] == '+'))
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			return (0);
		if (ft_isspace(arg[i]))
		{
			while (ft_isspace(arg[i]))
				i++;
			if (arg[i] == '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	if (!args)
		exit(0);
	if (args[1])
	{
		if (!is_number(args[1]))
			error(ft_strdup("numeric argument required"), EXIT, 255);
		if (args[2])
			return (error(ft_strdup("too many arguments"), RETURN, 1));
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(ft_atoi(args[1]));
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}
