/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_util.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 15:49:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 12:48:21 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
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

void	iter_tokens(t_token_list *l, int fd, void (*f)(char *, int))
{
	while (l)
	{
		f(l->content, fd);
		l = l->next;
	}
}
