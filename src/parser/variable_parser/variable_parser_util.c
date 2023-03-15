/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:03:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/15 11:19:52 by pmolnar       ########   odam.nl         */
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

t_var	*get_var_by_name(char *lookup_name, t_list *list)
{
	char	*declared_name;
	int		len;

	while (list)
	{
		declared_name = ((t_var *)list->content)->name;
		len = ft_strlen(lookup_name);
		if (!ft_strncmp(lookup_name, declared_name, len + 1))
			return (list->content);
		list = list->next;
	}
	return (NULL);
}

void	parse_var(char *s, t_var *var)
{
	char	*separator;
	int		size;

	separator = ft_strchr(s, EQUAL);
	size = separator - s;
	var->name = ft_substr(s, 0, size);
	s += size + 1;
	size = ft_strlen(s);
	var->val = ft_substr(s, 0, size);
}
