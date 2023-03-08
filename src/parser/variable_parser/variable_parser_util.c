/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:03:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/08 15:12:15 by pmolnar       ########   odam.nl         */
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
	if (s[i++] != EQUAL)
		return (0);
	while (s[i] && ft_isalnum(s[i]))
		i++;
	return (1);
}

t_list	*find_var_by_name(t_var *var, t_list *list)
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

void	extract_var_parts(char *s, t_var *var)
{
	char	**splitted_str;

	splitted_str = ft_split(s, EQUAL);
	if (splitted_str[0])
		var->name = splitted_str[0];
	if (splitted_str[1])
		var->val = splitted_str[1];
}
