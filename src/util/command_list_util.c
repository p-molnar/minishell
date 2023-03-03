/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_list_util.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 14:43:08 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/03 16:48:38 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_data_types.h>
#include <ms_macros.h>
#include <stdio.h>
#include <stdlib.h>

void		copy_token(t_token_list **copy, t_token_list *original)
{
	if (original)
		add_node_last(copy, new_node(ft_strdup(original->content), original->type));
}

void		copy_phrase(t_token_list **copy, t_token_list *original)
{
	while (original)
	{
		if (original->type == WORD)
			add_node_last(copy, new_node(ft_strdup(original->content), original->type));
		else
			break ;
		original = original->next;
	}
}

t_command_list	*new_command_node(int symbol, t_token_list *phrase)
{
	t_command_list	*command;

	command = malloc(sizeof(t_command_list));
	if (command == NULL)
		return (NULL);
	command->symbol = symbol;
	command->phrase = phrase;
	command->next = NULL;
	return (command);
}

void	add_command_back(t_command_list **list, t_command_list *node)
{
	t_command_list	*tmp_ptr;

	if (list && node)
	{
		if (!*list)
			*list = new_command_node(node->symbol, node->phrase);
		else
		{
			tmp_ptr = *list;
			while (tmp_ptr->next)
				tmp_ptr = tmp_ptr->next;
			tmp_ptr->next = node;
		}
	}
}

void	free_command_list(t_command_list *list)
{
	t_command_list	*tmp_ptr;

	while (list)
	{
		tmp_ptr = list->next;
		if (list->phrase)
			free_list(list->phrase);
		free(list);
		list = tmp_ptr;
	}
}
