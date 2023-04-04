/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:15:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/04 23:18:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <minishell.h>
#include <ms_data_types.h>
#include <stdio.h>
#include <stdlib.h>

int	is_valid_var_definition(char *s)
{
	char	*sep;
	int		len;

	sep = ft_strchr(s, EQUAL);
	if (sep != NULL)
	{
		len = sep - s;
		if (is_valid_var_name(s, len))
			return (1);
	}
	return (0);
}

void	parse_shell_variable(t_shell_data *data)
{
	t_token_list	*token_list;
	t_var			*var;

	token_list = data->tokens;
	while (token_list)
	{
		if (is_valid_var_definition(token_list->content))
		{
			var = parse_var_def(token_list->content);
			var->type = SHL;
			add_var(var, &data->variables);
		}
		token_list = token_list->next;
	}
}

void	parse_env_variable(char **env_arr, t_list **list)
{
	char	*var_def;
	t_var	*var_parsed;

	while (env_arr && *env_arr)
	{
		var_def = *env_arr;
		var_parsed = parse_var_def(var_def);
		var_parsed->type = SHL | ENV;
		add_var(var_parsed, list);
		env_arr++;
	}
}
