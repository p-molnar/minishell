/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/28 17:36:57 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/28 17:37:32 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

char	*var_to_str(t_var *var)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(var->name, "=");
	str2 = ft_strjoin(str1, var->val);
	free(str1);
	return (str2);
}

int		count_vars(t_list *var_list)
{
	int		i;

	i = 0;
	while (var_list)
	{
		i++;
		var_list = var_list->next;
	}
	return (i);
}

char	**env_builder(t_list *var_list)
{
	char 	**env;
	t_var	*var;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (count_vars(var_list) + 1));
	while (var_list)
	{
		var = var_list->content;
		if (var->name && var->val)
			env[i] = var_to_str(var);
		var_list = var_list->next;
		i++;
	}
	env[i] = NULL;
	return (NULL);
}
