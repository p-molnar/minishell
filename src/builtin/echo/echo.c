/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:41:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 18:18:07 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <unistd.h>

int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args && args[i])
	{
		while (ft_strncmp(args[i], "-n", 2 + 1) == 0)
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			i++;
			if (args[i])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
