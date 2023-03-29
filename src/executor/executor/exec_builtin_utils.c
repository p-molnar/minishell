/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 15:55:52 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/29 15:57:34 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token_list	*get_next_command(t_command_list *current)
{
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == CMD)
			return (current->token);
		current = current->next;
	}
	return (NULL);
}

t_token_list	*get_next_argument(t_command_list *current)
{
	while (current)
	{
		if (current->symbol == D_PIPE)
			break ;
		if (current->symbol == ARG)
			return (current->token);
		current = current->next;
	}
	return (NULL);
}
