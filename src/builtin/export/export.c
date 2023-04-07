/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 13:40:23 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 12:45:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <stdlib.h>
#include <stdio.h>

void	print_exported_vars(t_list *var_list)
{
	t_var	*curr_var;

	while (var_list)
	{
		curr_var = var_list->content;
		printf("declare -x ");
		if (curr_var->type & ENV)
		{
			if (curr_var->name && curr_var->val)
				printf("%s=\"%s\"", curr_var->name, curr_var->val);
			else if (curr_var->name && curr_var->val == NULL)
				printf("%s", curr_var->name);
			printf("\n");
		}
		var_list = var_list->next;
	}
}

int	export_vars(char *arg, t_list *var_list)
{
	t_var	*var;

	var = NULL;
	if (*arg == '\0' || *arg == ' ')
		return (error("not a valid identifier", RETURN, 1));
	else if (is_valid_var_definition(arg))
	{
		var = parse_var_def(arg);
		var->type = SHL | ENV;
		add_var(var, &var_list);
	}
	else if (is_valid_var_name(arg, ft_strlen(arg)))
	{
		var = get_var(arg, var_list, SHL);
		if (var)
			var->type |= ENV;
		else
		{
			var = create_var(ft_strdup(arg), NULL, SHL | ENV);
			add_var(var, &var_list);
		}
	}
	else
		return (error("not a valid identifier", RETURN, 1));
	return (EXIT_SUCCESS);
}

int	builtin_export(char **args, t_shell_data *data)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		print_exported_vars(data->variables);
	while (args && args[i])
	{
		if (export_vars(args[i], data->variables))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
