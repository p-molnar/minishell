/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   step_5.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 11:03:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/31 18:20:57 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
5. Starting with the first pathname in the <colon>-separated
pathnames of CDPATH (see the ENVIRONMENT VARIABLES section)
if the pathname is non-null, test if the concatenation of
that pathname, a <slash> character if that pathname did not
end with a <slash> character, and the directory operand names
a directory. If the pathname is null, test if the
concatenation of dot, a <slash> character, and the operand
names a directory. In either case, if the resulting string
names an existing directory, set curpath to that string and
proceed to step 7. Otherwise, repeat this step with the next
pathname in CDPATH until all pathnames have been tested.
*/

#include <ms_macros.h>
#include <minishell.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char	*yield_valid_cdpath(char *dir, char **path_comp)
{
	int		i;
	char	*new_path;

	i = 0;
	while (path_comp && path_comp[i])
	{
		new_path = path_concat(path_comp[i], dir);
		printf("test new_path: %s\n", new_path);
		if (access(new_path, (F_OK)) != -1)
		{
			printf("step5: file exists\n");
			return (new_path);
		}
		else
		{
			printf("step5: file doesn't exist\n");
			i++;
		}
	}
	return (NULL);
}

void	exec_step_5(char *dir, char **curpath, t_var **var, int *step)
{
	char	**path_comps;
	char	*new_path;

	if (var[CDPATH])
	{
		path_comps = ft_split(var[CDPATH]->val, ':');
		if (path_comps && (get_arr_size((void **)path_comps) > 0))
		{
			new_path = yield_valid_cdpath(dir, path_comps);
			if (new_path)
			{
				*curpath = new_path;
				*step = 7;
				return ;
			}
			free_arr((void **)path_comps);
		}
	}
	else
	{
		new_path = path_concat("./", dir);
		if (access(new_path, (F_OK | X_OK)) != -1) // test it!
		{
			*curpath = new_path;
			*step = 7;
			return ;
		}
	}
	*step += 1;
}
