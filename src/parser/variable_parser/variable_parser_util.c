/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_parser_util.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 15:03:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/04 16:03:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

int	is_valid_var_name(char *s, int n)
{
	int	i;

	i = 0;
	if (s[i] == '\0' || n == 0)
		return (0);
	while (s && s[i] != '\0' && n)
	{
		if (i == 0 && ft_isdigit(s[i]))
		{
			return (0);
		}
		else if (s[i] != '_' && !ft_isalnum(s[i]))
		{
			return (0);
		}
		i++;
		n--;
	}
	return (1);
}

t_var	*parse_var_def(char *s)
{
	char	*sep;
	char	*name;
	char	*val;
	int		size;

	if (!s)
		return (NULL);
	sep = ft_strchr(s, EQUAL);
	if (!sep)
		return (NULL);
	size = sep - s;
	name = ft_substr(s, 0, size);
	s += size + 1;
	size = ft_strlen(s);
	val = ft_substr(s, 0, size);
	return (create_var(name, val));
}
