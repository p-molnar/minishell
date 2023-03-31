/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:02:38 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 17:52:24 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	builtin_env(t_list *var_list)
{
	t_var	*var;

	while (var_list)
	{
		var = var_list->content;
		if (var->name && var->val)
			printf("%s=%s\n", var->name, var->val);
		var_list = var_list->next;
	}
	return (0);
}
