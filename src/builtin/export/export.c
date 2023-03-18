/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 13:40:23 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/18 20:13:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>

void	print_exported_vars(t_shell_data *data)
{
	(void) data;
	return ;
}

void	export(t_token_list *token, t_shell_data *data)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return ;
	if (token == NULL)
		print_exported_vars(data);
	else if (is_valid_var_definition(token->content))
		parse_var(token->content, var);
	else
	{
		var->name = token->content;
		var->val = NULL;
	}
	add_var(var, &data->env_vars);
}
