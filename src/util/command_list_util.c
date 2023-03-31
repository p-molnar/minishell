/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_list_util.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 14:43:08 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/31 12:51:01 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <stdlib.h>

t_command_list	*new_command_node(int symbol, t_token_list *token)
{
	t_command_list	*command;

	command = malloc(sizeof(t_command_list));
	if (command == NULL)
		return (NULL);
	command->symbol = symbol;
	command->token = token;
	command->next = NULL;
	return (command);
}

void	add_command_back(t_command_list **list, t_command_list *node)
{
	t_command_list	*tmp_ptr;

	if (list && node)
	{
		if (!*list)
			*list = node;
		else
		{
			tmp_ptr = *list;
			while (tmp_ptr->next)
				tmp_ptr = tmp_ptr->next;
			tmp_ptr->next = node;
		}
	}
}

void	free_command_list(t_command_list **list)
{
	t_command_list	*current;
	t_command_list	*previous;

	if (*list)
	{
		current = *list;
		while (current)
		{
			previous = current;
			current = current->next;
			free(previous);
			previous = NULL;
		}
		list = NULL;
	}
}
