/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/28 16:45:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

void	add_variable(t_list **str_list, char **s, t_shell_data *data)
{
	char	*var_name;
	t_var	*var;

	var_name = parse_var_name(*s);
	var = get_var(var_name, data->env_vars);
	if (var != NULL)
		ft_lstadd_back(str_list, ft_lstnew(ft_strdup(var->val)));
	*s += ft_strlen(var_name) + 1;
	free(var_name);
}

char	*expand_token(char *s, t_shell_data *data)
{
	t_list	*str_list;
	char	is_quoted;
	char	*expanded_s;

	str_list = NULL;
	is_quoted = 0;
	while (s && *s != '\0')
	{
		if ((*s == QUOTE || *s == DQUOTE) && !is_quoted)
			is_quoted = *s;
		else if (*s == is_quoted)
			is_quoted = 0;
		else if (*s == DOLLAR && (!is_quoted || is_quoted == DQUOTE))
		{
			add_variable(&str_list, &s, data);
			continue ;
		}
		else
			ft_lstadd_back(&str_list, ft_lstnew(chardup(s)));
		s++;
	}
	expanded_s = list_to_str(str_list);
	free_list(str_list);
	return (expanded_s);
}

void	expand_tokens(t_shell_data *data)
{
	t_token_list	*curr_token;
	char			*tmp_ptr;

	curr_token = data->tokens;
	while (curr_token)
	{
		tmp_ptr = curr_token->content;
		curr_token->content = expand_token(curr_token->content, data);
		free(tmp_ptr);
		curr_token = curr_token->next;
	}
}
