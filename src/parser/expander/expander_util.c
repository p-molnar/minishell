/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 09:50:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/06 12:39:54 by pmolnar       ########   odam.nl         */
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
		if (*s == DOLLAR && !ft_isdigit(*(s + 1)))
			count++;
		s++;
	}
	return (count);
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
