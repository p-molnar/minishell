/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/06 11:17:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>


static void	extract_var_names(char *s, t_var_list *list)
{
	char	*start_ptr;
	char	*end_ptr;

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
	int		i;
	char	*val;

	i = 0;
	while (i < var_count)
	{
		printf("var name: %s\n", list[i].name);
		val = getenv(list->name);
		if (!val)
			val = "";
		list[i].val = val;
		i++;
	}
}

char	*find_replace(char *needle, char *nail, char *haystack)
{
	char	*dst;
	int		size;
	int		offset;
	char	*needle_ptr;

	size = ft_strlen(haystack) + ft_strlen(nail) - ft_strlen(needle) + 1;
	dst = ft_calloc(size, sizeof(char));
	if (!dst)
		return (NULL);
	needle_ptr = ft_strchr(haystack, *needle);
	size = needle_ptr - haystack;
	ft_strlcpy(dst, haystack, size + 1);
	size = ft_strlen(nail) + 1;
	ft_strlcpy(ft_strchr(dst, '\0'), nail, size);
	offset = needle_ptr - haystack + ft_strlen(needle);
	size = ft_strlen(&haystack[offset]);
	ft_strlcpy(ft_strchr(dst, '\0'), &haystack[size], size + 1);
	free (haystack);
	return (dst);
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
		*s = find_replace(name, l->val, *s);
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
			// printf("token: |%s|\n", list->content);
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
