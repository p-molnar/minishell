/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_8.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:28:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/21 16:58:49 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>

/*
8. The curpath value shall then be converted to canonical form
	as follows, considering each component from beginning to end,
	in sequence:

	a. Dot components and any <slash> characters that separate
		them from the next component shall be deleted.

	b. For each dot-dot component, if there is a preceding
		component and it is neither root nor dot-dot, then:

		i.  If the preceding component does not refer (in the
			context of pathname resolution with symbolic links
			followed) to a directory, then the cd utility shall
			display an appropriate error message and no further
			steps shall be taken.

		ii.  The preceding component, all <slash> characters
			separating the preceding component from dot-dot,
			dot-dot, and all <slash> characters separating dot-
			dot from the following component (if any) shall be
			deleted.

	c. An implementation may further simplify curpath by
		removing any trailing <slash> characters that are not
		also leading <slash> characters, replacing multiple non-
		leading consecutive <slash> characters with a single
		<slash>, and replacing three or more leading <slash>
		characters with a single <slash>.  If, as a result of
		this canonicalization, the curpath variable is null, no
		further steps shall be taken.
*/

char	**remove_dot_comp(char **arr, int size)
{
	char	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arr = ft_calloc(size + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (arr && arr[j])
	{
		if (ft_strncmp(arr[j], ".", 2) != 0)
		{
			new_arr[i] = ft_strdup(arr[j]);
			new_arr[i + 1] = NULL;
			i++;
		}
		j++;
	}
	free_arr((void **)arr);
	return (new_arr);
}

char **dir_move_up(char **arr, int dd_comp_index)
{
	char	*path;

	if (dd_comp_index > 0 && ft_strncmp(arr[0], "..", 3) != 0)
	{
		path = n_arr_to_str(arr, "/", dd_comp_index - 1);
		printf("path: %s\n", path);
		// if (access(path, F_OK) != -1);
	}
	return (NULL);
}

char **process_dotdot_comp(char **arr, int size)
{
	int i;
	int	has_dotdot_comp;

	i = 0;
	has_dotdot_comp = 1;
	while (has_dotdot_comp)
	{
		while (i < size)
		{
			if (ft_strncmp(arr[i], "..", 3) == 0)
				dir_move_up(arr, i);
			i++;
		}
		
	}
	return (NULL);
}

int	exec_step_8(char **curpath, int *step)
{
	char	**comps;

	comps = ft_split(*curpath, '/');
	comps = remove_dot_comp(comps, get_arr_size((void **)comps));
	int i = 0;
	while (comps && comps[i])
	{
		printf("comps[%d]=%s\n", i, comps[i]);
		i++;
	}
	*step += 1;
	comps = process_dotdot_comp(comps, get_arr_size((void **)comps));
	return (0);
}
