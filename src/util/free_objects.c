/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 14:12:38 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 18:17:28 by pmolnar       ########   odam.nl         */
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
		if (token && token->content)
			free(token->content);
		if (token)
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

void	free_node(t_list **node)
{
	if (node && *node && (*node)->content)
		free((*node)->content);
	if (node && *node)
	{
		free(*node);
		*node = NULL;
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp_ptr;

	while (list)
	{
		tmp_ptr = list->next;
		free_node(&list);
		list = tmp_ptr;
	}
}

void	free_var(t_var **var)
{
	if (var && *var)
	{
		if ((*var)->name)
		{
			free((*var)->name);
			(*var)->name = NULL;
		}
		if ((*var)->val)
		{
			free((*var)->val);
			(*var)->val = NULL;
		}
		free(*var);
		*var = NULL;
	}
}

void	free_var_list(t_list *var_list)
{
	t_list	*tmp_list;

	while (var_list)
	{
		tmp_list = var_list;
		if (var_list->content)
			free_var(var_list->content);
		var_list = var_list->next;
		free(tmp_list);
	}
}

void	free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free (arr[i++]);
	if (arr)
		free (arr);
}
