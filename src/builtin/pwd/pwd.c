/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 10:22:01 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/14 10:35:44 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	pwd(t_shell_data *data)
{
	char	*cwd_path;
	(void)	data;

	cwd_path = getcwd(NULL, 0);
	printf("%s\n", cwd_path);
	free(cwd_path);
}
