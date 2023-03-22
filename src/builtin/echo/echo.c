/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 14:41:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/22 12:25:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>


void	echo(t_token_list *token)
{
	if (!token)
		return ;
	if (token->content && ft_strncmp(token->content, "echo", 4 + 1) == 0)
	{
		token = token->next;
		if (!token)
			return ;
	}
	if (token->content && ft_strncmp(token->content, "-n", 2 + 1) == 0)
		iter_tokens(token->next, 1, &ft_putstr_fd);
	else
		iter_tokens(token, 1, &ft_putendl_fd);
}
