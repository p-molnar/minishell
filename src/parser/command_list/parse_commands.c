/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:33:38 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/03/21 16:22:59 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>
#include <stdio.h>
#include <stddef.h>

int	add_command(t_command_list **command_list, t_token_list *token)
{
	if (is_valid_var_definition(token->content))
	{
		add_command_back(command_list, new_command_node(ASSIGNMENT, token));
		return (0);
	}
	else
		add_command_back(command_list, new_command_node(CMD, token));
	return (1);
}

int	add_simple_command(t_command_list **command_list, t_token_list *token)
{
	int		command_flag;
	int		ret;

	command_flag = 0;
	ret = 0;
	while (command_flag == 0 && token)
	{
		if (token->type == OPERATOR)
		{
			ret = parse_operator(command_list, token);
			if (ret)
				return (ret);
			token = token->next;
		}
		else if (token->type == WORD)
			command_flag = (add_command(command_list, token));
		token = token->next;
	}
	while (token)
	{
		if (token->type == OPERATOR)
		{
			ret = parse_operator(command_list, token);
			if (ret)
				return (ret);
			token = token->next;
		}
		else if (token->type == WORD)
			add_command_back(command_list, new_command_node(ARG, token));
		token = token->next;
	}
	return (0);
}

t_command_list	*parse_commands(t_token_list *token)
{
	t_command_list	*command_list;

	command_list = NULL;
	while (token)
	{
		if (token->type == OPERATOR && ft_strncmp(token->content, "|", 1) == 0)
		{
			printf("Syntax error, unexpected token %s\n", token->content);
			free_command_list(command_list);
			return (command_list);
		}
		if (token->type == INVALID || token->type == UNDEFINED)
		{
			printf("Syntax error, unexpected token %s\n", token->content);
			free_command_list(command_list);
			return (command_list);
		}
		if (add_simple_command(&command_list, token) == 2)
			return (NULL);
		while (token->next)
		{
			if (!(token->type == OPERATOR
					&& ft_strncmp(token->content, "|", 1) == 0))
				token = token->next;
			else
				break ;
		}
		if (token->type == OPERATOR && ft_strncmp(token->content, "|", 1) == 0)
		{
			add_command_back(&command_list, new_command_node(D_PIPE, NULL));
			if (!token->next)
			{
				printf("Syntax error, unexpected end of token list\n");
				free_command_list(command_list);
				return (NULL);
			}
		}
		token = token->next;
	}
	return (command_list);
}
