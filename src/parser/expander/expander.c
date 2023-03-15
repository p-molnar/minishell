/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 11:18:07 by pmolnar       ########   odam.nl         */
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
	char	*var_name;

	start_ptr = s;
	while (*start_ptr && ft_strchr(start_ptr, DOLLAR))
	{
		start_ptr = ft_strchr(start_ptr, DOLLAR) + 1;
		end_ptr = start_ptr;
		while (ft_isalnum(*end_ptr))
			end_ptr++;
		var_name = ft_substr(start_ptr, 0, end_ptr - start_ptr);
		if (*var_name == '\0')
			free (var_name);
		else
		{
			list->name = var_name;
			list++;
		}
		start_ptr += end_ptr - start_ptr;
	}
}

static void	get_var_values(t_var *var_arr, t_shell_data *data, int var_count)
{
	int		i;
	t_list	*var_node;

	i = 0;
	while (i < var_count)
	{
		var_node = get_var_by_name(var_arr[i].name, data->env_vars);
		if (var_node == NULL)
		{
			var_node = get_var_by_name(var_arr[i].name, data->shell_vars);
			if (var_node == NULL)
			{
				var_arr[i].val = ""; // read-only, problematic for free
				i++;
				continue ;
			}
		}
		var_arr[i].val = ((t_var *)var_node->content)->val;
		i++;
	}
}

static void	replace_vars_with_values(char **s, t_var *var_arr, int count)
{
	int		i;
	int		len;
	char	*dollar_prefixed_name;
	char	*ptr;

	i = 0;
	while (i < count)
	{
		ptr = *s;
		len = ft_strlen(var_arr[i].name);
		dollar_prefixed_name = malloc((len + 2) * sizeof(char));
		if (!dollar_prefixed_name)
			return ;
		dollar_prefixed_name[0] = DOLLAR;
		ft_strlcpy(&dollar_prefixed_name[1], var_arr[i].name, len + 1);
		*s = find_replace(dollar_prefixed_name, var_arr[i].val, *s);
		free (ptr);
		free (dollar_prefixed_name);
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
