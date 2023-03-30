/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 13:40:23 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 15:03:31 by pmolnar       ########   odam.nl         */
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
			printf("%s=\"%s\"", curr_var->name, curr_var->val);
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
	char	*s;

	if (token == NULL)
		return (print_exported_vars(data->env_vars));
	while (token)
	{
		s = token->content;
		if (s && *s == ' ')
			return ;
		else if (is_valid_var_definition(s))
			var = parse_var_def(s);
		else
		{
			var = get_var(s, data->shell_vars);
			if (!var)
				var = create_var(ft_strdup(token->content), NULL);
		}
		add_var(var, &data->env_vars);
		token = token->next;
	}
}
