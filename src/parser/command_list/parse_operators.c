/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_operators.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:59:33 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/09 16:01:47 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>
#include <stdio.h>

int		parse_redirect_out(t_command_list **command_list,
						t_token_list *token, int append_flag)
{
	if (!token->next)
	{
		printf("Syntax error, unexpected end of token list\n");
		return (2);
	}
	token = token->next;
	if (token->type != WORD)
	{
		printf("Syntax error, unexpected token %s\n", token->content);
		return (2);
	}
	if (append_flag == 0)
		add_command_back(command_list, new_command_node(OUTFILE, token));
	if (append_flag == 1)
		add_command_back(command_list, new_command_node(OUTFILE_APP, token));
	return (0);
}

int		parse_redirect_in(t_command_list **command_list,
						t_token_list *token)
{
	if (!token->next)
	{
		printf("Syntax error, unexpected end of token list\n");
		return (2);
	}
	token = token->next;
	if (token->type != WORD)
	{
		printf("Syntax error, unexpected token %s\n", token->content);
		return (2);
	}
		add_command_back(command_list, new_command_node(INFILE, token));
	return (0);
}

int		parse_operator(t_command_list **command_list, t_token_list *token)
{
	if (ft_strncmp(token->content, "|", 1) == 0)
		return (1);
	else if (ft_strncmp(token->content, ">>", 2) == 0)
		return (parse_redirect_out(command_list, token, 1));
	// else if (ft_strncmp(token->content, "<<", 2) == 0)
	// 	return parse_redirect_in_delimiter(command_list, token);
	else if (ft_strncmp(token->content, ">", 1) == 0)
		return (parse_redirect_out(command_list, token, 0));
	else if (ft_strncmp(token->content, "<", 1) == 0)
		return (parse_redirect_in(command_list, token));
	return (0);
}
