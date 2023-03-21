/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_operators.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:59:33 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/21 16:59:10 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>
#include <stdio.h>

int	parse_redirect_out(t_command_list **cmd_list,
						t_token_list *token, int append_flag)
{
	if (!token->next)
	{
		printf("Syntax error, unexpected end of token list\n");
		free_command_list(*cmd_list);
		return (RET_SYNTAX_ERR);
	}
	token = token->next;
	if (token->type != WORD)
	{
		printf("Syntax error, unexpected token %s\n", token->content);
		free_command_list(*cmd_list);
		return (RET_SYNTAX_ERR);
	}
	if (append_flag == 0)
		add_command_back(cmd_list, new_command_node(OUTFILE, token));
	if (append_flag == 1)
		add_command_back(cmd_list, new_command_node(OUTFILE_APP, token));
	return (RET_END);
}

int	parse_redirect_in(t_command_list **cmd_list,
						t_token_list *token, int heredoc_flag)
{
	if (!token->next)
	{
		printf("Syntax error, unexpected end of token list\n");
		free_command_list(*cmd_list);
		return (RET_SYNTAX_ERR);
	}
	token = token->next;
	if (token->type != WORD)
	{
		printf("Syntax error, unexpected token %s\n", token->content);
		free_command_list(*cmd_list);
		return (RET_SYNTAX_ERR);
	}
	if (heredoc_flag == 0)
		add_command_back(cmd_list, new_command_node(INFILE, token));
	if (heredoc_flag == 1)
		add_command_back(cmd_list,
			new_command_node(HEREDOC_DELIMITER, token));
	return (RET_END);
}

int	parse_operator(t_command_list **cmd_list, t_token_list *token)
{
	if (ft_strncmp(token->content, "|", 1) == 0)
		return (RET_PIPE);
	else if (ft_strncmp(token->content, ">>", 2) == 0)
		return (parse_redirect_out(cmd_list, token, 1));
	else if (ft_strncmp(token->content, "<<", 2) == 0)
		return (parse_redirect_in(cmd_list, token, 1));
	else if (ft_strncmp(token->content, ">", 1) == 0)
		return (parse_redirect_out(cmd_list, token, 0));
	else if (ft_strncmp(token->content, "<", 1) == 0)
		return (parse_redirect_in(cmd_list, token, 0));
	return (RET_END);
}
