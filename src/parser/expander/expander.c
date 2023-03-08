/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/06 13:13:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

static void	extract_var_names(char *s, t_var_list *list)
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

static void	get_var_values(t_var_list *list, int var_count)
{
	int		i;
	char	*val;

	i = 0;
	while (i < var_count)
	{
		val = getenv(list->name);
		if (!val)
			val = "";
		list[i].val = val;
		i++;
	}
}

static void	replace_vars_with_values(char **s, t_var_list *l, int count)
{
	int		i;
	int		len;
	char	*name;
	char	*tmp;

	i = 0;
	tmp = *s;
	while (i < count)
	{
		len = ft_strlen(l->name);
		name = malloc((len + 2) * sizeof(char));
		if (!name)
			return ;
		name[0] = DOLLAR;
		ft_strlcpy(&name[1], l->name, len + 1);
		*s = find_replace(name, l->val, *s);
		free (tmp);
		free (name);
		l++;
		i++;
	}
}

void	expand_tokens(t_token_list *list)
{
	t_var_list	*var_list;
	int			var_count;

	while (list)
	{
		var_count = count_var(list->content);
		if (var_count)
		{
			var_list = malloc(var_count * sizeof(t_var_list));
			if (!var_list)
				return ;
			extract_var_names(list->content, var_list);
			get_var_values(var_list, var_count);
			replace_vars_with_values(&list->content, var_list, var_count);
			// printf("token: |%s|\n", list->content);
			// for (int i = 0; i < var_count; i++)
			// {
			// 	printf("%d:\t%s=%s\n", i++, var_list->name, var_list->val);
			// 	// printf("%d:\t%s\n", i, var_list[i].key);
			// }
			free (var_list);
		}
		list = list->next;
	}
}
