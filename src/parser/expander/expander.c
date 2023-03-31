/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/30 17:31:25 by pmolnar       ########   odam.nl         */
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
	char	*str;
	t_var	*var;

	var_name = parse_var_name(*s);
	var = get_var(var_name, data->env_vars);
	if (var == NULL)
		var = get_var(var_name, data->shell_vars);
	if (var)
	{
		if (!var->val)
			str = ft_strdup("");
		else
			str = ft_strdup(var->val);
	}
	else if (*var_name == '\0')
		str = chardup(*s);
	else if (*var_name == '?')
		str = ft_itoa(WEXITSTATUS(g_exit_status));
	else
		str = ft_strdup("");
	ft_lstadd_back(str_list, ft_lstnew(str));
	*s += ft_strlen(var_name);
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
		if (ft_strchr(QUOTES, *s) && !is_quoted)
			is_quoted = *s;
		else if (is_quoted && *s == is_quoted)
			is_quoted = 0;
		else if (*s == DOLLAR && (!is_quoted || is_quoted == DQUOTE))
			add_variable(&str_list, &s, data);
		else
			ft_lstadd_back(&str_list, ft_lstnew(chardup(s)));
		s++;
	}
	expanded_s = list_to_str(str_list);
	free_list(&str_list);
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
