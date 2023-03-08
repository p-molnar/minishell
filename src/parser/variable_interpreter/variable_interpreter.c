/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_interpreter.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:15:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/08 14:40:57 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <ms_data_types.h>
#include <stdio.h>
#include <stdlib.h>

static void	extract_var_parts(char *s, t_var *var)
{
	char	**splitted_str;

	splitted_str = ft_split(s, EQUAL);
	if (splitted_str[0])
		var->name = splitted_str[0];
	if (splitted_str[1])
		var->val = splitted_str[1];
}

static int	is_valid_var_definition(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i++]))
		return (0);
	while (ft_isalnum(s[i]))
		i++;
	if (s[i++] != EQUAL)
		return (0);
	while (s[i] && ft_isalnum(s[i]))
		i++;
	return (1);
}

static t_list	*find_var_by_name(t_var *var, t_list *list)
{
	char	*lookup_name;
	char	*declared_name;

	lookup_name = var->name;
	while (list)
	{
		declared_name = ((t_var *)list->content)->name;
		if (!ft_strncmp(lookup_name, declared_name, ft_strlen(lookup_name)))
			return (list);
		list = list->next;
	}
	return (NULL);
}

static void	add_shell_var(t_var *new_var, t_list **list)
{
	t_list	*new_node;
	t_list	*defined_var;
	t_var	*old_var;

	defined_var = find_var_by_name(new_var, *list);
	if (!defined_var)
	{
		new_node = ft_lstnew(new_var);
		if (!new_node)
			return ;
		ft_lstadd_back(list, new_node);
	}
	else
	{
		old_var = defined_var->content;
		if (!ft_strncmp(old_var->val, new_var->val, ft_strlen(new_var->val)))
			return ;
		free(old_var->val);
		old_var->val = new_var->val;
	}

}

void	parse_variable(t_shell_data *data)
{
	t_token_list	*list;
	t_var			*var;

	list = data->tokens;
	while (list)
	{
		if (is_valid_var_definition(list->content))
		{
			var = ft_calloc(1, sizeof(t_var));
			if (!var)
				return ;
			extract_var_parts(list->content, var);
			add_shell_var(var, &data->shell_vars);
		}
		list = list->next;
	}
}
