/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 14:12:38 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/23 15:47:49 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <stdlib.h>
#include <stdio.h>

void	free_token_list(t_token_list *list)
{
	t_token_list	*tmp_ptr;

	while (list)
	{
		tmp_ptr = list;
		if (tmp_ptr->content)
			free(tmp_ptr->content);
		list = list->next;
		free(tmp_ptr);
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp_ptr;

	while (list)
	{
		tmp_ptr = list;
		if (tmp_ptr->content)
			free(tmp_ptr->content);
		list = list->next;
		free(tmp_ptr);
	}
}
void	free_var_list(t_list *var_list)
{
	t_list	*tmp_list;
	t_var	*tmp_var;

	while (var_list)
	{
		tmp_list = var_list;
		if (tmp_list->content)
		{
			tmp_var = tmp_list->content;
			if (tmp_var->name)
				free(tmp_var->name);
			if (tmp_var->val)
				free(tmp_var->val);
		}
		var_list = var_list->next;
		free(tmp_list);
	}
}
