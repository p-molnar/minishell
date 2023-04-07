/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/06 13:56:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/07 10:30:19 by pmolnar       ########   odam.nl         */
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
	r = NULL;
	tmp = NULL;
	while (n > 0)
	{
		arg = va_arg(ap, char *);
		if (!arg)
			arg = "";
		if (!r)
			r = ft_strjoin("", arg);
		else
			r = ft_strjoin(r, arg);
		if (!r)
		{
			free_obj((void **)&tmp);
			return (NULL);
		}
		free_obj((void **)&tmp);
		tmp = r;
		n--;
	}
	va_end(ap);
	return (r);
}
