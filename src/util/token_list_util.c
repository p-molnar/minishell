/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_util.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 15:49:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 10:37:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <stdio.h>
#include <stdlib.h>

t_token_list	*new_node(char *content, int token_type)
{
	t_token_list	*token;

	if (content != NULL)
	{
		token = malloc(sizeof(t_token_list));
		if (token == NULL)
			return (NULL);
		token->content = content;
		// token->prompt_ptr = tkn_start; might be useful later.
		token->type = token_type;
		token->next = NULL;
		return (token);
	}
	return (NULL);
}

void	add_node_last(t_token_list **list, t_token_list *node)
{
	t_token_list	*tmp_ptr;

	if (list && node)
	{
		if (!*list)
			*list = new_node(node->content, node->type);
		else
		{
			tmp_ptr = *list;
			while (tmp_ptr->next)
				tmp_ptr = tmp_ptr->next;
			tmp_ptr->next = node;
		}
	}
}

void	iter_tokens(t_token_list *l, int fd, void (*f)(char *, int))
{
	while (l)
	{
		f(l->content, fd);
		l = l->next;
	}
}
