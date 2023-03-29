/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/29 10:37:37 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 10:38:07 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>

t_list	*get_node(void *lookup_content, t_list *list)
{
	while (list)
	{
		if (list->content == lookup_content)
			return (list);
		list = list->next;
	}
	return (NULL);
}
