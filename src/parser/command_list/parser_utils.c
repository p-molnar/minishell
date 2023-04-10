/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 16:57:16 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/10 16:26:00 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command_list	*syntax_error(t_command_list **list, t_token_list *token)
{
	char	*err_msg;

	if (!token)
		error(ft_strdup("syntax error: unexpected end of token list"),
			RETURN, 258);
	else
	{
		err_msg = strconcat(3, "syntax error near unexpected token `",
				token->content, "'");
		error(err_msg, RETURN, 258);
	}
	free_command_list(list);
	return (NULL);
}
