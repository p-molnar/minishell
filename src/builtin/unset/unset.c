/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:17:39 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/30 11:18:13 by pmolnar       ########   odam.nl         */
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

void	del_node(t_list **list, t_list *node)
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

void	unset(char *var_name, t_shell_data *data)
{
	t_list	*env_ptr;
	t_list	*shell_ptr;

	if (!var_name || !data)
		return ;
	shell_ptr = get_node(get_var(var_name, data->shell_vars), data->shell_vars);
	env_ptr = get_node(get_var(var_name, data->env_vars), data->env_vars);
	// ptr = shell_ptr;
	if (shell_ptr && env_ptr)
	{
		del_node(&data->shell_vars, shell_ptr);
		del_node(&data->env_vars, env_ptr);
	}
	else if (shell_ptr)
		del_node(&data->shell_vars, shell_ptr);
	else if (env_ptr)
	{
		del_node(&data->env_vars, env_ptr);
		// ptr = env_ptr;
	}
	if (!shell_ptr && !env_ptr)
		return ;
	// free(((t_var *) ptr->content)->name);
	// free(((t_var *) ptr->content)->val);
	// free(ptr->content);
	// free(ptr);
}
