/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:41:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/14 14:47:26 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

void	echo(char *flag, char *s)
{
	if (!s)
		return ;
	if (flag && (ft_strncmp(flag, "-n", ft_strlen("-n") + 1) == 0))
		ft_putstr_fd(s, 1);
	else
		ft_putendl_fd(s, 1);
}
