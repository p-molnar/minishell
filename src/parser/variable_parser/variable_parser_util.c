/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:03:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/28 12:34:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>

t_var	*get_var(char *var_name, t_list *var_list)
{
	t_var	*var_declared;
	char	*name_declared;
	int		len;

	while (var_name && var_list)
	{
		var_declared = var_list->content;
		if (var_declared && var_declared->name)
		{
			name_declared = var_declared->name;
			len = ft_strlen(var_name);
			if (ft_strncmp(var_name, name_declared, len + 1) == 0)
				return (var_list->content);
		}
		var_list = var_list->next;
	}
	return (NULL);
}

void	add_var(t_var *new_var, t_list **var_list)
{
	t_var	*var_defined;
	t_var	*old_var;

	var_defined = get_var(new_var->name, *var_list);
	if (!var_defined)
		ft_lstadd_back(var_list, ft_lstnew(new_var));
	else
	{
		old_var = var_defined;
		if (old_var->val)
			free(old_var->val);
		old_var->val = new_var->val;
	}
}

t_list	*get_node(void *lookup_content, t_list *list)
{
	while (list)
	{
		if (list->content == lookup_content)
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_var	*parse_var(char *s)
{
	char	*sep;
	int		size;
	t_var	*var;

	if (!s)
		return (NULL);
	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	sep = ft_strchr(s, EQUAL);
	if (!sep)
		return (NULL);
	size = sep - s;
	var->name = ft_substr(s, 0, size);
	s += size + 1;
	size = ft_strlen(s);
	var->val = ft_substr(s, 0, size);
	return (var);
}
