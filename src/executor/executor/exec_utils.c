/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 13:43:17 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/07 18:39:16 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <stdlib.h>
#include <unistd.h>

char	*canonicalize_path(char *s)
{
	char	*new_path;
	int		on_slash;
	int		i;
	int		j;

	on_slash = 0;
	i = 0;
	j = 0;
	if (s)
	{
		new_path = ft_calloc(ft_strlen(s) + 1, sizeof(s));
		while (s[i])
		{
			if (s[i] == '/' && !on_slash)
			{
				on_slash = 1;
				new_path[j++] = s[i++];
			}
			else if (s[i] == '/' && on_slash)
				i++;
			else
			{
				new_path[j++] = s[i++];
				on_slash = 0;
			}
		}
		return (new_path);
	}
	return (NULL);
}

char	**get_path_to_bin(t_shell_data *data, char *cmd)
{
	t_var	*var;
	char	**bin_path;
	char	*finalpath;
	char	*tmp;
	int		i;

	i = 0;
	var = get_var("PATH", data->variables, ENV);
	if (!var)
		return (NULL);
	bin_path = ft_split(var->val, ':');
	if (!bin_path)
		return (NULL);
	while (bin_path[i])
	{
		finalpath = path_concat(bin_path[i], cmd);
		tmp = finalpath;
		finalpath = canonicalize_path(finalpath);
		free(tmp);
		free(bin_path[i]);
		bin_path[i] = finalpath;
		i++;
	}
	return (bin_path);
}

char	**compound_args(t_command_list *current)
{
	char	**arguments;
	int		arg_n;
	int		i;

	i = 0;
	arg_n = count_symbols_simple_cmd(ARG, current);
	arguments = malloc(sizeof(char *) * (arg_n + 2));
	if (!arguments)
		return (NULL);
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
