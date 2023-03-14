/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 16:17:39 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/14 10:57:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <libft.h>

void	del_node(t_list **list, t_list *node)
{
	t_list	*prev_node;
	t_list	*tmp;

	prev_node = NULL;
	tmp = *list;
	while (tmp)
	{
		if (tmp == node)
		{
			if (prev_node == NULL)
				*list = tmp->next;
			else if (tmp->next == NULL)
				prev_node->next = NULL;
			else
				prev_node->next = tmp->next;
			return ;
		}
		prev_node = tmp;
		tmp = tmp->next;
	}
}

void	unset(char *var_name, t_shell_data *data)
{
	t_list	*env_ptr;
	t_list	*shell_ptr;
	t_var	tmp_var;

	tmp_var.name = var_name;
	tmp_var.val = "";
	shell_ptr = find_var_by_name(&tmp_var, data->shell_vars);
	if (shell_ptr)
		del_node(&data->shell_vars, shell_ptr);
	else
		return ;
	env_ptr = find_var_by_name(&tmp_var, data->env_vars);
	if (env_ptr)
		del_node(&data->env_vars, env_ptr);
	free(((t_var *) shell_ptr->content)->name);
	free(((t_var *) shell_ptr->content)->val);
	free(shell_ptr->content);
	free(shell_ptr);
}
