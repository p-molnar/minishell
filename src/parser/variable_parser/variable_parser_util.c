/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:03:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 11:35:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdlib.h>

int	is_valid_var_name(char *s, int n)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0' && n)
	{
		if (i == 0 && ft_isdigit(s[i]))
			return (0);
		else if (s[i] != '_' && !ft_isalnum(s[i]))
			return (0);
		i++;
		n--;
	}
	return (1);
}

t_var	*get_var(char *lookup_name, t_list *var_list)
{
	t_var	*var;
	char	*var_name;
	int		len;

	while (lookup_name && var_list)
	{
		var = var_list->content;
		if (var && var->name)
		{
			var_name = var->name;
			len = ft_strlen(var_name);
			if (ft_strncmp(var_name, lookup_name, len + 1) == 0)
				return (var_list->content);
		}
		var_list = var_list->next;
	}
	return (NULL);
}

void	update_var(t_var *old_var, t_var *new_var)
{
	if (old_var && new_var)
	{
		if (old_var->val && new_var->val)
		{
			if (old_var == new_var)
				return ;
			else if (ft_strncmp(old_var->val, new_var->val,
					ft_strlen(old_var->val)) == 0)
			{
				free_var_obj(new_var);
				return ;
			}
			free(old_var->val);
			old_var->val = new_var->val;
			free(new_var->name);
			free(new_var);
		}
	}
}

void	add_var(t_var *new_var_def, t_list **var_list)
{
	t_var	*var_defined;
	t_var	*old_var_def;

	if (!new_var_def || !var_list)
		return ;
	var_defined = get_var(new_var_def->name, *var_list);
	if (var_defined)
	{
		old_var_def = var_defined;
		update_var(old_var_def, new_var_def);
	}
	else
		ft_lstadd_back(var_list, ft_lstnew(new_var_def));
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
