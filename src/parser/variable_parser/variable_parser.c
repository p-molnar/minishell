/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:15:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 11:35:39 by pmolnar       ########   odam.nl         */
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
		return (is_valid_var_name(s, len));
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
			var = parse_var(token_list->content);
			add_var(var, &data->shell_vars);
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
		var_parsed = parse_var(var_def);
		add_var(var_parsed, list);
		env_arr++;
	}
}
