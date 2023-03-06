/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 09:50:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/06 09:54:42 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_macros.h>
#include <libft.h>

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
