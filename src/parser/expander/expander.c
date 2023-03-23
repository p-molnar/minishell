/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/23 11:30:24 by pmolnar       ########   odam.nl         */
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

char	*chardup(char *s)
{
	char	*new_s;

	if (!s)
		return (NULL);
	new_s = ft_calloc(2, sizeof(char));
	new_s[0] = *s;
	return (new_s);
}

int	get_total_strlen(t_list *l)
{
	int	len;

	len = 0;
	while (l)
	{
		if (l->content)
			len += ft_strlen(l->content);
		l = l->next;
	}
	return (len);
}

char	*list_to_str(t_list *l)
{
	int		total_len;
	char	*curr_content;
	char	*str;
	int		i;

	total_len = get_total_strlen(l);
	str = ft_calloc(total_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (l)
	{
		curr_content = l->content;
		while (curr_content && *curr_content)
			str[i++] = *curr_content++;
		l = l->next;
	}
	return (str);
}

char	*expand_token(char *s, t_shell_data *data)
{
	t_list	*str_list;
	t_var	*var;
	char	*tmp;
	char	quoted;

	str_list = NULL;
	quoted = 0;
	while (s && *s != '\0')
	{
		if ((*s == QUOTE || *s == DQUOTE) && !quoted)
			quoted = *s;
		else if (*s == quoted)
			quoted = 0;
		else if (*s == DOLLAR && (!quoted || quoted == DQUOTE))
		{
			tmp = parse_var_name(s);
			var = get_var(tmp, data->env_vars);
			if (var != NULL)
				ft_lstadd_back(&str_list, ft_lstnew(var->val));
			s += ft_strlen(tmp) + 1;
			free(tmp);
			continue ;
		}
		else
		{
			tmp = chardup(s);
			ft_lstadd_back(&str_list, ft_lstnew(tmp));
		}
		s++;
	}
	return (list_to_str(str_list));
}

void	expand_tokens(t_shell_data *data)
{
	t_token_list	*curr_token;

	curr_token = data->tokens;
	while (curr_token)
	{
		curr_token->content = expand_token(curr_token->content, data);
		curr_token = curr_token->next;
	}
}
