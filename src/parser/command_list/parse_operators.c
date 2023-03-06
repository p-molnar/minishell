/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_operators.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 14:59:33 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/06 17:26:44 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>
#include <stdio.h>

//any syntax error should cause immediate cleanup and return to the prompt

void	parse_redirect_out(t_token_list *token, t_command_list **command_list,
						t_token_list *start_phrase, int append_flag)
{
	t_token_list	*copy;

	copy = NULL;
	add_command(command_list, start_phrase);
	add_command_back(command_list, new_command_node(D_REDIRECT_OUT, NULL));
	if (!token->next)
		printf("Syntax error, unexpected end of token list\n");
	token = token->next;
	if (token->type != WORD)
		printf("Syntax error, unexpected token %s\n", token->content);
	copy_token(&copy, token);
	if (append_flag == 0)
		add_command_back(command_list, new_command_node(OUTFILE, copy));
	if (append_flag == 1)
		add_command_back(command_list, new_command_node(OUTFILE_APP, copy));
	if (token->next)
		printf("Syntax error, unexpected token %s\n", token->next->content);
}

void	parse_pipe(t_token_list *token, t_command_list **command_list,
						t_token_list *start_phrase)
{
	add_command(command_list, start_phrase);
	add_command_back(command_list, new_command_node(D_PIPE, NULL));
	if (!token->next)
		printf("Syntax error, unexpected end of token list\n");
}

void	parse_operator(t_token_list *token, t_command_list **command_list,
						t_token_list *start_phrase)
{
	if (ft_strncmp(token->content, "|", 1) == 0)
		parse_pipe(token, command_list, start_phrase);
	else if (ft_strncmp(token->content, ">", 1) == 0)
		parse_redirect_out(token, command_list, start_phrase, 0);
	// else if (ft_strncmp(token->content, "<", 1) == 0)
	// 	parse_redirect_in(token, command_list, start_phrase);
	else if (ft_strncmp(token->content, ">>", 2) == 0)
		parse_redirect_out(token, command_list, start_phrase, 1);
	// else if (ft_strncmp(token->content, "<<", 2) == 0)
	// 	parse_redirect_in(token, command_list, start_phrase);
}
