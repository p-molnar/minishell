/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:46:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/23 13:27:33 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ms_data_types.h>
#include <ms_macros.h>
#include <minishell.h>
#include <libft.h>
#include <stdlib.h>

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
