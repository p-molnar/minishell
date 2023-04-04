/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:17:39 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/04 23:54:31 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <libft.h>

void	del_first_node(t_list **list)
{
	t_list	*next_node;

	if (list && *list)
	{
		next_node = (*list)->next;
		free_var((t_var **)&((*list)->content));
		free_node(list);
		*list = next_node;
	}
}

void	del_middle_node(t_list *prev_node, t_list *curr_node)
{
	if (prev_node && curr_node)
	{
		prev_node->next = curr_node->next;
		free_var((t_var **)(&curr_node->content));
		free_node(&curr_node);
	}
}

void	del_last_node(t_list **prev_node)
{
	if (prev_node && *prev_node)
	{
		free_var((t_var **)&((*prev_node)->next->content));
		free_node(&((*prev_node)->next));
		(*prev_node)->next = NULL;
	}
}

void	del_node(t_list *node, t_list **list)
{
	t_list	*prev_node;
	t_list	*curr;

	prev_node = NULL;
	curr = *list;
	while (curr)
	{
		if (curr == node)
		{
			if (prev_node == NULL)
				del_first_node(list);
			else if (curr->next == NULL)
				del_last_node(&prev_node);
			else
				del_middle_node(prev_node, curr);
			return ;
		}
		prev_node = curr;
		curr = curr->next;
	}
}

void	builtin_unset(char **args, t_shell_data *data)
{
	char	*name;
	t_list	*var_node;

	args++;
	while (args && *args)
	{
		name = *args;
		if (!name || !data)
			return ;
		var_node = get_node(get_var(name, data->variables, ENV), data->variables);
		if (var_node)
			del_node(var_node, &data->variables);
		args++;
	}
}
