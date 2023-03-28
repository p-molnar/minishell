/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 13:55:12 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/28 14:07:10 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

void	builtin_exit(char **args)
{
	if (args)
		exit(0);
}
