/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 14:12:38 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 09:48:07 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <stdlib.h>
#include <stdio.h>

void	free_token(t_token_list *token)
{
	if (token)
	{
		if (token->content)
			free(token->content);
		free(token);
	}
}

void	free_token_list(t_token_list *list)
{
	t_token_list	*tmp_ptr;
	t_token_list	*curr_node;

	curr_node = list;
	while (curr_node)
	{
		tmp_ptr = curr_node->next;
		free_token(curr_node);
		curr_node = tmp_ptr;
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

void	free_var_obj(t_var *var)
{
	if (var)
	{
		if (var->name)
			free(var->name);
		if (var->val)
			free(var->val);
		free(var);
	}
}

void	free_var_list(t_list *var_list)
{
	t_list	*tmp_list;

	while (var_list)
	{
		tmp_list = var_list;
		if (var_list->content)
			free_var_obj(var_list->content);
		var_list = var_list->next;
		free(tmp_list);
	}
}
