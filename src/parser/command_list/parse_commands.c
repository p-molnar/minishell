/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:33:38 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/06 17:26:44 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>
#include <stdio.h>
#include <stddef.h>

//any syntax error should cause immediate cleanup and return to the prompt

void	add_command(t_command_list **command_list, t_token_list *start_phrase)
{
	t_token_list	*phrase;

	phrase = NULL;
	if (start_phrase)
	{
		copy_token(&phrase, start_phrase);
		add_command_back(command_list, new_command_node(CMD, phrase));
		phrase = NULL;
		if (start_phrase->next)
		{
			start_phrase = start_phrase->next;
			if (start_phrase->type == WORD)
			{
				copy_phrase(&phrase, start_phrase);
				add_command_back(command_list, new_command_node(ARG, phrase));
			}
		}
	}
}

t_command_list	*parse_commands(t_token_list *token)
{
	t_command_list	*command_list;
	t_token_list	*start_phrase;

	command_list = NULL;
	start_phrase = token;
	while (token)
	{
		start_phrase = token;
		if (token->type != WORD)
		{
			printf("Syntax error, unexpected token %s\n", token->content);
			return (command_list);
		}
		while (token->next && token->type == WORD)
			token = token->next;
		if (token)
		{
			// if (token->type != OPERATOR)
			// {
			// 	printf("Syntax error, unknown token\n");
			// 	return (command_list);
			// }
			parse_operator(token, &command_list, start_phrase);
			token = token->next;
		}
	}
	add_command(&command_list, start_phrase);
	return (command_list);
}
