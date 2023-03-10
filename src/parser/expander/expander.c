/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/10 23:49:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

static void	extract_var_names(char *s, t_var *list)
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

static void	get_var_values(t_var *list, int var_count)
{
	int		i;
	char	*val;

	i = 0;
	while (i < var_count)
	{
		val = getenv(list[i].name);
		if (!val)
			val = "";
		list[i].val = val;
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

void	expand_tokens(t_token_list *list)
{
	t_var	*var_list;
	int		var_count;

	while (list)
	{
		var_count = count_var(list->content);
		if (var_count)
		{
			var_list = malloc(var_count * sizeof(t_var));
			if (!var_list)
				return ;
			extract_var_names(list->content, var_list);
			get_var_values(var_list, var_count);
			replace_vars_with_values(&list->content, var_list, var_count);
			free (var_list);
		}
		list = list->next;
	}
}
