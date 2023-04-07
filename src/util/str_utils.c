/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 13:56:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 13:02:09 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>
#include <stdlib.h>
#include <minishell.h>

char	*strconcat(int n, ...)
{
	va_list	ap;
	char	*tmp;
	char	*r;
	char	*arg;

	va_start(ap, n);
	r = "";
	tmp = NULL;
	while (n-- > 0)
	{
		arg = va_arg(ap, char *);
		if (!arg)
			arg = "";
		r = ft_strjoin(r, arg);
		free_obj((void **)&tmp);
		tmp = r;
		if (!r)
			return (NULL);
	}
	va_end(ap);
	return (r);
}
