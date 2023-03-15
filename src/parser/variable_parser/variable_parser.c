/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:15:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 11:45:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <minishell.h>
#include <ms_data_types.h>
#include <stdio.h>
#include <stdlib.h>

void	add_var(t_var *new_var, t_list **list)
{
	t_list	*new_node;
	t_var	*defined_var;
	t_var	*old_var;
	int		len;

	defined_var = get_var_by_name(new_var->name, *list);
	if (!defined_var)
	{
		new_node = ft_lstnew(new_var);
		if (!new_node)
			return ;
		ft_lstadd_back(list, new_node);
	}
	else
	{
		old_var = defined_var;
		len = ft_strlen(new_var->val);
		if (!ft_strncmp(new_var->val, old_var->val, len + 1))
			return ;
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

void	parse_env_variable(char **env, t_list **list)
{
	char	*var_definition;
	t_var	*var;

	while (*env)
	{
		var = ft_calloc(1, sizeof(t_var));
		if (!var)
			return ;
		var_definition = *env;
		parse_var(var_definition, var);
		add_var(var, list);
		env++;
	}
}
