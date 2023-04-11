/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_operations.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:00:06 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/11 09:48:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

t_var	*get_var(char *lookup_name, t_list *var_list, int var_type)
{
	t_var	*var;
	int		len;

	while (lookup_name && var_list)
	{
		var = var_list->content;
		if (var && var->name)
		{
			len = ft_strlen(var->name);
			if (ft_strncmp(var->name, lookup_name, len + 1) == 0
				&& (var->type & var_type))
			{
				return (var);
			}
		}
		var_list = var_list->next;
	}
	return (NULL);
}

t_var	*create_var(char *name, char *val, int type)
{
	t_var	*var;

	if (!name)
		return (NULL);
	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = name;
	var->val = val;
	var->type = type;
	return (var);
}

void	update_var(t_var *var, t_var *new_var)
{
	char	*tmp;

	tmp = NULL;
	if (var && new_var)
	{
		tmp = var->val;
		var->val = new_var->val;
		var->type |= new_var->type;
		free_obj((void **)&tmp);
		free_obj((void **)&new_var->name);
		free_obj((void **)&new_var);
	}
}

void	add_var(t_var *new_var_def, t_list **var_list)
{
	t_var	*var_defined;
	t_var	*old_var_def;

	if (!new_var_def || !var_list)
		return ;
	var_defined = get_var(new_var_def->name, *var_list, SHL | ENV);
	if (var_defined)
	{
		old_var_def = var_defined;
		update_var(old_var_def, new_var_def);
	}
	else
		ft_lstadd_back(var_list, ft_lstnew(new_var_def));
}
