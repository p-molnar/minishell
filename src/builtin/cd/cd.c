/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 15:10:22 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/17 10:31:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <ms_macros.h>
#include <libft.h>

void	str_preprocess(char **dir, t_var **var)
{
	char	*pwd;
	char	*tmp;
	int		len;

	pwd = var[PWD]->val;
	len = ft_strlen(pwd);
	tmp = pwd;
	if (pwd[len - 1] != '/')
	{
		tmp = ft_strjoin(pwd, "/");
		if (!tmp)
			return ;
	}
	tmp = ft_strjoin(tmp, *dir);
	if (!tmp)
		return ;
	*dir = tmp;
}

void	cd(char *dir, t_shell_data *data)
{
	t_var	*var[ENV_SIZE];

	var[HOME] = get_var("HOME", data->env_vars);
	var[PWD] = get_var("PWD", data->env_vars);
	var[OLDPWD] = get_var("PWD", data->env_vars);
	if (!dir || *dir == '\0')
	{
		if (var[HOME] == NULL || *var[HOME]->val == '\0')
			return ;
		cd (var[HOME]->val, data);
	}
	else if (*dir == '/')
	{
		if (var[PWD])
			update_wdirs(ft_strdup(dir), var, data);
	}
	else if (*dir != '/')
	{
		str_preprocess(&dir, var);
		cd(dir, data);
	}
}

