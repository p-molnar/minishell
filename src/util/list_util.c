/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 10:37:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/04 23:43:08 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>

t_list	*get_node(void *lookup_node, t_list *list)
{
	while (list)
	{
		if (list->content == lookup_node)
			return (list);
		list = list->next;
	}
	return (NULL);
}
