/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 16:57:16 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/03 16:57:52 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command_list	*syntax_error(t_command_list **list, t_token_list *token)
{
	char	*err_tkn;
	char	*err_msg;

	if (!token)
		error("Syntax error: unexpected end of token list", RETURN, 258);
	else
	{
		err_tkn = ft_strjoin(token->content, "'");
		err_msg = ft_strjoin("Syntax error near unexpected token '", err_tkn);
		error(err_msg, RETURN, 258);
		free(err_tkn);
		free(err_msg);
	}
	free_command_list(list);
	return (NULL);
}
