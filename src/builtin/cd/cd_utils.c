/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/21 11:18:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/03 11:15:02 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

char	*path_concat(char *basepath, char *relpath)
{
	char	*joined_str;
	char	*basepath_postfixed;

	joined_str = NULL;
	if (basepath && basepath[ft_strlen(basepath)- 1] != '/')
	{
		basepath_postfixed = ft_strjoin(basepath, "/");
		if (!basepath_postfixed)
			return (NULL);
		joined_str = ft_strjoin(basepath_postfixed, relpath);
		free(basepath_postfixed);
		if (!joined_str)
			return (NULL);
	}
	return (joined_str);
}

int	get_arr_size(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	*strnjoin(char **arr, char *el_delim, int n)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = ft_strdup("");
	while (arr && arr[i] && n-- > 0)
	{
		tmp = str;
		str = ft_strjoin(tmp, el_delim);
		free(tmp);
		tmp = str;
		str = ft_strjoin(tmp, arr[i++]);
		free(tmp);
	}
	if (str[0] == '\0')
	{
		free(str);
		str = ft_strdup("/");
	}
	return (str);
}
