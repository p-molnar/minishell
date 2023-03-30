/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 11:18:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/29 15:11:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

char	*path_concat(char *basepath, char *relpath)
{
	int		len[2];
	char	*joined_str;

	len[0] = ft_strlen(basepath);
	len[1] = ft_strlen(relpath);
	if (basepath[len[0] - 1] != '/')
	{
		basepath = ft_strjoin(basepath, "/");
		if (!basepath)
			return (NULL);
	}
	if (relpath[len[1] - 1] != '/')
	{
		relpath = ft_strjoin(relpath, "/");
		if (!relpath)
			return (NULL);
	}
	joined_str = ft_strjoin(basepath, relpath);
	if (!joined_str)
		return (NULL);
	return (joined_str);
	//	proper freeing
}

int	get_arr_size(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	*n_arr_to_str(char **arr, char *el_delim, int n)
{
	int		i;
	char	*str;
	char	*tmp;
	char	*tmp2;

	i = 0;
	str = ft_strdup("");
	while (arr && arr[i] && n > 0)
	{
		if (i > 0)
		{
			free(tmp);
			free(tmp2);
		}
		tmp = str;
		str = ft_strjoin(tmp, el_delim);
		tmp2 = str;
		str = ft_strjoin(tmp2, arr[i]);
		i++;
		n--;
	}
	if (str[0] == '\0')
	{
		free(str);
		str = ft_strdup("/");
	}
	return (str);
}
