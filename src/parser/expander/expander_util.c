/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 09:50:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/12 17:10:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <libft.h>
#include <stdlib.h>

int	count_var(char *s)
{
	int	count;

	count = 0;
	while (*(s + 1))
	{
		if (*s == DOLLAR && ft_isalpha(*(s + 1)))
			count++;
		s++;
	}
	return (count);
}

char	*find_replace(char *needle, char *repl, char *haystack)
{
	char	*dst;
	int		size;
	int		offset;
	char	*needle_ptr;

	size = ft_strlen(haystack) + ft_strlen(repl) - ft_strlen(needle);
	dst = ft_calloc(size + 1, sizeof(char));
	if (!dst)
		return (NULL);
	needle_ptr = ft_strchr(haystack, *needle);
	size = needle_ptr - haystack;
	ft_strlcpy(dst, haystack, size + 1);
	size = ft_strlen(repl);
	ft_strlcpy(ft_strchr(dst, '\0'), repl, size + 1);
	offset = needle_ptr - haystack + ft_strlen(needle);
	size = ft_strlen(&haystack[offset]);
	ft_strlcpy(ft_strchr(dst, '\0'), &haystack[offset], size + 1);
	return (dst);
}
