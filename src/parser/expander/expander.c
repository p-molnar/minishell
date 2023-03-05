/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/05 23:53:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	count_var(char *s)
{
	int	count;

	count = 0;
	while (*(s + 1))
	{
		if (*s == DOLLAR && !ft_isdigit(*(s + 1)))
			count++;
		s++;
	}
	return count;
}

static void extract_var_names(char *s, t_var_list *list)
{
	char *start_ptr;
	char *end_ptr;

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
	int	i;

	i = 0;
	while (i < var_count)
	{
		printf("val: %s\n", list[i].name);
		list[i].val = getenv(list->name);
		i++;
	}
}

void	find_replace(char *needle, char *nail, char **haystack)
{
	char	*dst;
	char	*ptr;
	char	*start;
	int		size;	

	dst = malloc((ft_strlen(*haystack) + ft_strlen(nail) - ft_strlen(needle) + 1) * sizeof(char));
	if (!dst)
		return ;
	ptr = ft_strchr(*haystack, *needle);
	size = ptr - *haystack;
	start = *haystack;
	ft_strlcpy(dst, start, size);
	ft_strlcpy(&dst[size], nail, ft_strlen(nail));
	size += ft_strlen(nail);
	start = haystack[ptr - *haystack + ft_strlen(needle)];
	ft_strlcpy(&dst[size], start, ft_strlen(start));
	*haystack = dst;
}

void	replace_vars_with_values(char **s, t_var_list *l, int count)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	while (i < count)
	{
		len = ft_strlen(l->name);
		name = malloc((len + 2) * sizeof(char));
		if (!name)
			return ;
		name[0] = DOLLAR;
		ft_strlcpy(&name[1], l->name, len + 1); //??
		find_replace(name, l->val, s);
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
			printf("-new token-\n");
			printf("token: |%s|\n", list->content);
			// for (int i = 0; i < var_count; i++)
			// {
			// 	printf("%d:\t%s=%s\n", i++, var_list->name, var_list->val);
			// 	// printf("%d:\t%s\n", i, var_list[i].key);
			// }

			// while (var_list)
			// {
			// 	printf("%s\n", var_list->key);
			// 	var_list++;
			// }
			free (var_list);
		}
		list = list->next;
	}
};