/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_objects_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 16:04:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/11 10:12:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_data_types.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>

void	free_var_list(t_list *var_list)
{
	t_list	**list;
	t_list	*next;

	list = &var_list;
	while (list && *list)
	{
		next = (*list)->next;
		if ((*list)->content)
			free_var((t_var **)&(*list)->content);
		free(*list);
		*list = next;
	}
}

void	free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free (arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
	{
		free (arr);
		arr = NULL;
	}	
}

void	free_obj(void **obj)
{
	if (obj && *obj)
	{
		free(*obj);
		*obj = NULL;
	}
}

void	cleanup_before_exit(t_shell_data *data)
{
	tcsetattr(0, 0, &data->original_termios);
	clear_history();
}
