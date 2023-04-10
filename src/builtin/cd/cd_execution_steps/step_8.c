/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_8.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 15:28:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/10 11:48:42 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void	remove_consecutive_slashes(char *dst, char *src)
{
	int		on_slash;
	int		i;
	int		j;

	on_slash = 0;
	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '/' && !on_slash)
		{
			on_slash = 1;
			dst[j] = src[i];
			j++;
		}
		else if (src[i] == '/' && on_slash)
			;
		else
		{
			dst[j] = src[i];
			on_slash = 0;
			j++;
		}
		i++;
	}
}

char	*canonicalize_path(char *s)
{
	char	*new_path;

	new_path = ft_calloc(ft_strlen(s) + 1, sizeof(s));
	if (!new_path)
		return (NULL);
	if (!s)
	{
		free_obj((void **)&new_path);
		return (NULL);
	}
	remove_consecutive_slashes(new_path, s);
	return (new_path);
}

int	exec_step_8(char **curpath, int *step)
{
	char	**comps;
	char	**dptr_tmp;

	comps = ft_split(*curpath, '/');
	dptr_tmp = comps;
	free_obj((void **)&(*curpath));
	comps = remove_dot_comp(comps, get_arr_size((void **)comps));
	free_arr((void **)dptr_tmp);
	dptr_tmp = comps;
	*curpath = process_dotdot_comp(comps);
	free_arr((void **)dptr_tmp);
	*step += 1;
	if (curpath == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
