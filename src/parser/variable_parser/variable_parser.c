/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:15:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/26 23:52:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <minishell.h>
#include <ms_data_types.h>
#include <stdio.h>
#include <stdlib.h>

void	add_var(t_var *new_var, t_list **var_list)
{
	t_var	*var_defined;
	t_var	*old_var;

	var_defined = get_var(new_var->name, *var_list);
	if (!var_defined)
		ft_lstadd_back(var_list, ft_lstnew(new_var));
	else
	{
		old_var = var_defined;
		if (old_var->val)
			free(old_var->val);
		old_var->val = new_var->val;
	}
}

void	parse_shell_variable(t_shell_data *data)
{
	t_token_list	*list;
	t_var			*var;

	list = data->tokens;
	while (list)
	{
		if (is_valid_var_definition(list->content))
		{
			var = ft_calloc(1, sizeof(t_var));
			if (!var)
				return ;
			parse_var(list->content, var);
			add_var(var, &data->shell_vars);
		}
		list = list->next;
	}
}

void	parse_env_variable(char **env_arr, t_list **list)
{
	char	*var_def;
	t_var	*var_parsed;

	while (env_arr && *env_arr)
	{
		var_parsed = ft_calloc(1, sizeof(t_var));
		if (!var_parsed)
			return ;
		var_def = *env_arr;
		parse_var(var_def, var_parsed);
		add_var(var_parsed, list);
		env_arr++;
	}
}
