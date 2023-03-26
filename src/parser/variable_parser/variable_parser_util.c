/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:03:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/26 23:33:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>

int	is_valid_var_definition(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[i++]))
		return (0);
	while (ft_isalnum(s[i]))
		i++;
	if (s[i] != EQUAL)
		return (0);
	// while (s[i] && ft_isalnum(s[i]))
	// 	i++;
	return (1);
}

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

void	parse_var(char *s, t_var *var)
{
	char	*separator;
	int		size;

	if (s)
		return ;
	separator = ft_strchr(s, EQUAL);
	if (!separator)
		return ;
	size = separator - s;
	var->name = ft_substr(s, 0, size);
	s += size + 1;
	size = ft_strlen(s);
	var->val = ft_substr(s, 0, size);
}
