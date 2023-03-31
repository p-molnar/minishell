/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 10:22:01 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 17:30:04 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	builtin_pwd(t_shell_data *data)
{
	t_var	*var;

	var = get_var("PWD", data->env_vars);
	if (var && var->val)
		printf("%s\n", var->val);
	else
		return (error("", RETURN, 1));
	return (0);
}
