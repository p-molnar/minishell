/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_8_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 09:29:44 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/04 09:57:49 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char	**remove_dot_comp(char **arr, int size)
{
	char	**new_arr;
	int		i;
	int		j;

	new_arr = ft_calloc(size + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (arr && arr[j])
	{
		if (ft_strncmp(arr[j], ".", 2) != 0)
			new_arr[i++] = ft_strdup(arr[j]);
		j++;
	}
	return (new_arr);
}

char	**dir_move_up(char **arr, int dd_comp_index)
{
	char	**processed_arr;
	int		i;
	int		j;

	processed_arr = ft_calloc(get_arr_size((void **)arr), sizeof(char *));
	if (!processed_arr)
		return (NULL);
	if (dd_comp_index > 0 && ft_strncmp(arr[0], "..", 3) != 0)
	{
		i = 0;
		j = 0;
		while (arr && arr[i])
		{
			if (i == dd_comp_index - 1)
			{
				i++;
				continue ;
			}
			processed_arr[j] = arr[i];
			i++;
			j++;
		}
		return (processed_arr);
	}
	return (NULL);
}

char	**move_up_dir(char **arr, int dd_comp_idx)
{
	char	**new_arr;
	int		j;
	int		k;

	new_arr = ft_calloc(get_arr_size((void **)arr) + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	j = 0;
	k = 0;
	while (arr && arr[j])
	{
		if (j == dd_comp_idx || j == dd_comp_idx - 1)
		{
			j++;
			continue ;
		}
		new_arr[k++] = arr[j++];
	}
	return (new_arr);
}

char	*process_dotdot_comp(char **arr)
{
	int		i;
	char	*path;
	char	**tmp_arr;

	i = 0;
	tmp_arr = arr;
	while (tmp_arr && tmp_arr[i])
	{
		tmp_arr = arr;
		if (ft_strncmp(tmp_arr[i], "..", 3) == 0)
		{
			path = strnjoin(tmp_arr, "/", i - 1);
			if (access(path, F_OK) != -1)
			{
				free(path);
				tmp_arr = move_up_dir(tmp_arr, i);
				free
				i = 0;
				continue ;
			}
		}
		i++;
	}
	path = strnjoin(tmp_arr, "/", get_arr_size((void **)tmp_arr));
	// free_arr((void **) arr);
	return (path);
}
