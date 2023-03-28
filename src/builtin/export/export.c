/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 13:40:23 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/28 12:07:04 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>

void	print_exported_vars(t_list *var_list)
{
	t_var	*curr_var;

	while (var_list)
	{
		curr_var = var_list->content;
		printf("declare -x ");
		if (curr_var->name && curr_var->val)
			printf("%s=%s", curr_var->name, curr_var->val);
		else if (curr_var->name && curr_var->val == NULL)
			printf("%s", curr_var->name);
		printf("\n");
		var_list = var_list->next;
	}
	return ;
}

void	export(t_token_list *token, t_shell_data *data)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return ;
	if (token == NULL)
	{
		print_exported_vars(data->env_vars);
		return ;
	}
	else if (is_valid_var_definition(token->content))
		parse_var(var, token->content);
	else
	{
		var->name = ft_strdup(token->content); // check for return val!
		var->val = NULL;
	}
	add_var(var, &data->env_vars);
}
