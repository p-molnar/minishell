/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 15:10:22 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/20 14:13:34 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

// char	*slash_preprocess(char *basepath, char *relpath)
// {
// 	int		len[2];
// 	char	*strjoin;

// 	len[0] = ft_strlen(basepath);
// 	len[1] = ft_strlen(relpath);
// 	if (basepath[len[0] - 1] != '/')
// 	{
// 		basepath = ft_strjoin(basepath, "/");
// 		if (!basepath)
// 			return (NULL);
// 	}
// 	if (relpath[len[1] - 1] != '/')
// 	{
// 		relpath = ft_strjoin(relpath, "/");
// 		if (!relpath)
// 			return (NULL);
// 	}
// 	strjoin = ft_strjoin(basepath, relpath);
// 	if (!strjoin)
// 		return (NULL);
// 	return (strjoin);
// 	//	proper freeing
// }

// char	**remove_dot_comp(char **arr, int size)
// {
// 	char	**new_arr;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new_arr = ft_calloc(size + 1, sizeof(char *));
// 	if (!new_arr)
// 		return (NULL);
// 	while (arr && arr[j])
// 	{
// 		if (ft_strncmp(arr[j], ".", 2) != 0)
// 		{
// 			new_arr[i] = ft_strdup(arr[j]);
// 			new_arr[i + 1] = NULL;
// 			i++;
// 		}
// 		j++;
// 	}
// 	free(arr);
// 	return (new_arr);
// }

// int	get_arr_size(void **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr && arr[i])
// 		i++;
// 	return (i);
// }

// char	*dot_preprocess(char *dir)
// {
// 	char	**comp;
// 	char	*path;
// 	char	*ptr;
// 	int		i;

// 	comp = ft_split(*dir, '/');
// 	comp = remove_dot_comp(comp, get_arr_size((void **)comp));
// 	path = "";
// 	i = 0;
// 	while (comp && comp[i])
// 	{
// 		if (i > 0)
// 			free(ptr);
// 		path = ft_strjoin(path, comp[i]);
// 		ptr = path;
// 		i++;
// 	}
// }

// void	look_in_cdpath(char **dir, t_var **var, t_shell_data *data)
// {
// 	int		i;
// 	char	**path;
// 	char	*new_dir;

// 	i = 0;
// 	path = ft_split(var[CDPATH]->val, ':');
// 	if (!path)
// 		return ;
// 	while (path && path[i])
// 	{
// 		new_dir = slash_preprocess(path[i], *dir);
// 		// test if lib exists
// 		printf("new_dir %s\n", new_dir);
// 		i++;
// 	}
// 	dot_preprocess(dir, var, data);
// }

void	init_env_vars(t_var **env_var, t_shell_data *data)
{
	env_var[HOME] = get_var("HOME", data->env_vars);
	env_var[PWD] = get_var("PWD", data->env_vars);
	env_var[OLDPWD] = get_var("OLDPWD", data->env_vars);
	env_var[CDPATH] = get_var("CDPATH", data->env_vars);
}

// follows man page logic
// https://man7.org/linux/man-pages/man1/cd.1p.html

int	cd(char *dir, t_shell_data *data)
{
	t_var	*env_var[ENV_SIZE];
	char	*curpath;
	int		step;


	step = 1;
	curpath = NULL;
	init_env_vars(env_var, data);
	if (step == 1)
	{
		exec_step_1(env_var, &dir, data);
		step++;
	}
	// if (*dir == '/')
	// {
	// 	curpath = dir;
	// 	exec_rule_1();
	// }
	// if (ft_split(dir, '/')[0] == '.')
	// {
	// 	curpath = dir;
	// 	// dot_preprocess(&dir, env_var, data);
	// }
	// if (curpath != '/')
	// {
	// 	slash_preprocess(var[PWD]->val, curpath);
	// }
	// else
	// {
	// 	look_in_cdpath(&dir, env_var, data);
	// }
	// // else if (*dir != '/')
	// // {
	// // 	cd(curpath, data);
	// // }
	return (update_wdirs(curpath, env_var, data));
}

