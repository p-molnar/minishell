/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:15:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/28 11:50:11 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <minishell.h>
#include <ms_data_types.h>
#include <stdio.h>
#include <stdlib.h>

int	is_valid_var_definition(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i++]))
		return (0);
	while (ft_isalnum(s[i]))
		i++;
	if (s[i] != EQUAL)
		return (0);
	return (1);
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
			var = ft_calloc(1, sizeof(t_var));
			if (!var)
				return ;
			parse_var(token_list->content, var);
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
		var_parsed = ft_calloc(1, sizeof(t_var));
		if (!var_parsed)
			return ;
		var_def = *env_arr;
		parse_var(var_def, var_parsed);
		add_var(var_parsed, list);
		env_arr++;
	}
}
