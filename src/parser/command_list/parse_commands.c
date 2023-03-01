/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:33:38 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/01 18:32:10 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>
#include <stdio.h>
#include <stddef.h>

void	add_final_command(t_command_list **command_list, t_token_list *start_phrase)
{
	t_token_list	*phrase;

	phrase = NULL;
	if (start_phrase)
		add_command_back(command_list, new_command_node(CMD, start_phrase));
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

void	add_pipe_command(t_command_list **command_list, t_token_list *start_phrase)
{
	t_token_list	*phrase;

	phrase = NULL;
	if (start_phrase)
		add_command_back(command_list, new_command_node(CMD, start_phrase));
	if (start_phrase->next)
	{
		start_phrase = start_phrase->next;
		if (start_phrase->type == WORD)
		{
			copy_phrase(&phrase, start_phrase);
			add_command_back(command_list, new_command_node(ARG, phrase));
		}
	}
	add_command_back(command_list, new_command_node(D_PIPE, NULL));
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
			if (ft_strncmp(token->content, "|", 1) == 0)
			{
				add_pipe_command(&command_list, start_phrase);
				start_phrase = NULL;
			}
			token = token->next;
		}
	}
	add_final_command(&command_list, start_phrase);
	return (command_list);
}
