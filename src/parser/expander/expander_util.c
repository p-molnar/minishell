/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 09:50:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/28 17:18:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

char	*parse_var_name(char *s)
{
	char	*start_ptr;
	char	*end_ptr;
	char	*var_name;

	start_ptr = s + 1;
	end_ptr = start_ptr;
	while (!ft_strchr(DELIM_CHARS, *end_ptr) && *end_ptr != DOLLAR)
		end_ptr++;
	var_name = ft_substr(start_ptr, 0, end_ptr - start_ptr);
	if (*var_name == '\0')
		free (var_name);
	return (var_name);
}

char	*chardup(char *s)
{
	char	*new_s;

	if (!s)
		return (NULL);
	new_s = ft_calloc(2, sizeof(char));
	new_s[0] = *s;
	return (new_s);
}

int	get_total_strlen(t_list *l)
{
	int	len;

	len = 0;
	while (l)
	{
		if (l->content)
			len += ft_strlen(l->content);
		l = l->next;
	}
	return (len);
}

char	*list_to_str(t_list *l)
{
	int		total_len;
	char	*curr_content;
	char	*str;
	int		i;

	total_len = get_total_strlen(l);
	str = ft_calloc(total_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (l)
	{
		curr_content = l->content;
		while (curr_content && *curr_content)
			str[i++] = *curr_content++;
		l = l->next;
	}
	return (str);
}
