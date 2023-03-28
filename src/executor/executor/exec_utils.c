/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 13:43:17 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/28 15:47:27 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <stdlib.h>

char	**path_builder(t_shell_data *data)
{
	t_var	*var;
	char	**path;
	char	*finalpath;
	int		i;

	i = 0;
	var = get_var("PATH", data->env_vars);
	if (!var)
		return (NULL);
	path = ft_split(var->val, ':');
	while (path[i])
	{
		finalpath = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = finalpath;
		i++;
	}
	return (path);
}

char	**compound_args(t_command_list *current)
{
	char	**arguments;
	int		arg_n;
	int		i;

	i = 0;
	arg_n = count_symbols_simple_cmd(ARG, current);
	arguments = malloc(sizeof(char *) * (arg_n + 2));
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == ARG || current->symbol == CMD)
		{
			arguments[i] = current->token->content;
			i++;
		}
		current = current->next;
	}
	arguments[i] = NULL;
	return (arguments);
}

int	count_symbols(int symbol, t_command_list *current)
{
	int		count;

	count = 0;
	while (current)
	{
		if (current->symbol == symbol)
			count++;
		current = current->next;
	}
	return (count);
}

int	count_symbols_simple_cmd(int symbol, t_command_list *current)
{
	int		count;

	count = 0;
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == symbol)
			count++;
		current = current->next;
	}
	return (count);
}
