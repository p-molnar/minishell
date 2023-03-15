/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 13:40:23 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 11:59:15 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>

void	export(t_token_list *token, t_shell_data *data)
{
	t_var	tmp_var;
	t_var	*var;

	if (is_valid_var_definition(token->content))
		parse_var(token->content, &tmp_var);
	else
		tmp_var.name = token->content;
	var = get_var(tmp_var.name, data->shell_vars);
	if (!var)
		return ;
	add_var(var, &data->env_vars);
}
