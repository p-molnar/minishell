/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/12 15:36:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

static void	parse_var_names(char *s, t_var *list)
{
	char	*start_ptr;
	char	*end_ptr;

	start_ptr = s;
	while (*start_ptr && ft_strchr(start_ptr, DOLLAR))
	{
		start_ptr = ft_strchr(start_ptr, DOLLAR) + 1;
		end_ptr = start_ptr + 1;
		while (ft_isalnum(*end_ptr))
			end_ptr++;
		list->name = ft_substr(start_ptr, 0, end_ptr - start_ptr);
		list++;
		start_ptr += end_ptr - start_ptr;
	}
}

static void	get_var_values(t_var *var_list, t_shell_data *data, int var_count)
{
	int		i;
	t_list	*var_node;

	i = 0;
	while (i < var_count)
	{
		var_node = find_var_by_name(&var_list[i], data->env_vars);
		if (var_node == NULL)
		{
			var_node = find_var_by_name(&var_list[i], data->shell_vars);
			if (var_node == NULL)
			{
				var_list[i].val = ""; // read-only, probelmatic for free
				i++;
				continue ;
			}
		}
		var_list[i].val = ((t_var *)var_node->content)->val;
		i++;
	}
}

static void	replace_vars_with_values(char **s, t_var *l, int count)
{
	int		i;
	int		len;
	char	*name;
	char	*tmp;

	i = 0;
	while (i < count)
	{
		tmp = *s;
		len = ft_strlen(l[i].name);
		name = malloc((len + 2) * sizeof(char));
		if (!name)
			return ;
		name[0] = DOLLAR;
		ft_strlcpy(&name[1], l[i].name, len + 1);
		*s = find_replace(name, l[i].val, *s);
		free (tmp);
		free (name);
		i++;
	}
}

void	expand_tokens(t_shell_data *data)
{
	t_token_list	*token;
	int				var_count;
	t_var			*tmp_var_arr;

	token = data->tokens;
	while (token)
	{
		var_count = count_var(token->content);
		if (var_count > 0)
		{
			tmp_var_arr = malloc(var_count * sizeof(t_var));
			if (!tmp_var_arr)
				return ;
			parse_var_names(token->content, tmp_var_arr);
			get_var_values(tmp_var_arr, data, var_count);
			replace_vars_with_values(&token->content, tmp_var_arr, var_count);
			free (tmp_var_arr);
		}
		token = token->next;
	}
}
