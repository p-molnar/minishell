/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:17:39 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 15:42:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <libft.h>

void	del_first_node(t_list **curr_node)
{
	t_list	*next_node;

	next_node = (*curr_node)->next;
	free_node(*curr_node);
	*curr_node = next_node;
}

void	del_middle_node(t_list *prev_node, t_list *curr_node)
{
	prev_node->next = curr_node->next;
	free(curr_node);
}

void	del_last_node(t_list *prev_node)
{
	free_node(prev_node->next);
	prev_node->next = NULL;
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
				del_first_node(&node);
			else if (curr->next == NULL)
				del_last_node(node);
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
	t_list	*ptr;

	if (!var_name)
		return ;
	shell_ptr = get_node(get_var(var_name, data->shell_vars), data->shell_vars);
	env_ptr = get_node(get_var(var_name, data->env_vars), data->env_vars);
	ptr = shell_ptr;
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
		ptr = env_ptr;
	}
	if (!shell_ptr && !env_ptr)
		return ;
	free(((t_var *) ptr->content)->name);
	free(((t_var *) ptr->content)->val);
	free(ptr->content);
	free(ptr);
}
