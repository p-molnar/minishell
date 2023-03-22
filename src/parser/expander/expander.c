/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/22 17:01:56 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

char	*parse_var_name(char *s)
{
	char	*start_ptr;
	char	*end_ptr;
	char	*var_name;

	start_ptr = s + 1;
	end_ptr = start_ptr;
	while (!ft_strchr(DELIM_CHARS, *end_ptr))
		end_ptr++;
	var_name = ft_substr(start_ptr, 0, end_ptr - start_ptr);
	if (*var_name == '\0')
		free (var_name);
	return (var_name);
}

// static void	get_var_values(t_var *var_arr, t_shell_data *data, int var_count)
// {
// 	int		i;
// 	t_var	*var;

// 	i = 0;
// 	while (i < var_count)
// 	{
// 		var = get_var(var_arr[i].name, data->env_vars);
// 		if (var == NULL)
// 		{
// 			var = get_var(var_arr[i].name, data->shell_vars);
// 			if (var == NULL)
// 			{
// 				var_arr[i].val = ""; // read-only, problematic for free
// 				i++;
// 				continue ;
// 			}
// 		}
// 		var_arr[i].val = var->val;
// 		i++;
// 	}
// }

// static void	replace_vars_with_values(char **s, t_var *var_arr, int count)
// {
// 	int		i;
// 	int		len;
// 	char	*dollar_prefixed_name;
// 	char	*ptr;

// 	i = 0;
// 	while (i < count)
// 	{
// 		ptr = *s;
// 		len = ft_strlen(var_arr[i].name);
// 		dollar_prefixed_name = malloc((len + 2) * sizeof(char));
// 		if (!dollar_prefixed_name)
// 			return ;
// 		dollar_prefixed_name[0] = DOLLAR;
// 		ft_strlcpy(&dollar_prefixed_name[1], var_arr[i].name, len + 1);
// 		*s = find_replace(dollar_prefixed_name, var_arr[i].val, *s);
// 		free (ptr);
// 		free (dollar_prefixed_name);
// 		i++;
// 	}
// }

void	expand_tokens(t_shell_data *data)
{
	t_token_list	*token;
	// int				var_count;
	// t_var			*tmp_var_arr;
	char			*s;
	char			quoted;
	char			*expanded_s;
	int				i;

	token = data->tokens;
	while (token)
	{
		s = token->content;
		quoted = 0;
		expanded_s = ft_calloc(ft_strlen(s) + 1, sizeof(char));
		if (!expanded_s)
			return ;
		i = 0;
		while (*s != '\0')
		{
			if (*s == QUOTE || *s == DQUOTE)
			{
				if (!quoted)
					quoted = *s;
				else if (*s == quoted)
					quoted = 0;
				else if (*s != quoted)
					expanded_s[i++] = *s;
				s++;
				continue ;
			}
			else if (*s == DOLLAR && (!quoted || quoted == DQUOTE))
			{
				char *var = parse_var_name(s);
				printf("var: |%s|\n", var);
				t_var *varobj = get_var(var, data->env_vars);
				expanded_s = ft_strjoin(expanded_s, varobj->name);
				// replace_vars_with_values(&token->content, tmp_var_arr, var_count);
				// free(tmp_var_arr);
			}
			expanded_s[i] = *s;
			i++;
			s++;
		}
		token->content = expanded_s;
		// var_count = count_var(token->content);
		// if (var_count > 0)
		// {
		// 	tmp_var_arr = malloc(var_count * sizeof(t_var));
		// 	if (!tmp_var_arr)
		// 		return ;
		// 	parse_var_name(token->content, tmp_var_arr);
		// 	get_var_values(tmp_var_arr, data, var_count);
		// 	replace_vars_with_values(&token->content, tmp_var_arr, var_count);
		// 	free(tmp_var_arr);
		// }
		token = token->next;
	}
}
