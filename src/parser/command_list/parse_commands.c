/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jzaremba <jzaremba@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:33:38 by jzaremba      #+#    #+#                 */
/*   Updated: 2023/04/07 17:36:44 by jzaremba      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <ms_macros.h>

int	add_command(t_command_list **command_list, t_token_list *token)
{
	if (is_valid_var_definition(token->content))
	{
		add_command_back(command_list, new_command_node(ASSIGNMENT, token));
		return (RET_END);
	}
	else
		add_command_back(command_list, new_command_node(CMD, token));
	return (RET_PIPE);
}

int	add_arguments(t_command_list **command_list, t_token_list *token)
{
	int	ret;

	ret = RET_END;
	while (token)
	{
		if (token->type & OPERATOR)
		{
			ret = parse_operator(command_list, token);
			if (ret)
				return (ret);
			token = token->next;
		}
		else if (token->type & WORD)
			add_command_back(command_list, new_command_node(ARG, token));
		token = token->next;
	}
	return (ret);
}

int	add_simple_command(t_command_list **command_list, t_token_list *token)
{
	int		command_flag;
	int		ret;

	command_flag = 0;
	ret = RET_END;
	while (command_flag == 0 && token)
	{
		if (token->type & OPERATOR)
		{
			ret = parse_operator(command_list, token);
			if (ret)
				return (ret);
			token = token->next;
		}
		else if (token->type & WORD)
			command_flag = (add_command(command_list, token));
		token = token->next;
	}
	add_arguments(command_list, token);
	return (ret);
}

t_command_list	*check_token(t_command_list **command_list, t_token_list *token)
{
	if (token->type & OPERATOR && ft_strncmp(token->content, "|", 1) == 0)
		return (syntax_error(command_list, token));
	if (token->type & INVALID || token->type & UNDEFINED)
		return (syntax_error(command_list, token));
	if (add_simple_command(command_list, token) == RET_SYNTAX_ERR)
		return (NULL);
	return (*command_list);
}

t_command_list	*parse_commands(t_token_list *token)
{
	t_command_list	*command_list;

	command_list = NULL;
	while (token)
	{
		if (!check_token(&command_list, token))
			return (NULL);
		while (token->next)
		{
			if (!(token->type & OPERATOR
					&& ft_strncmp(token->content, "|", 1) == 0))
				token = token->next;
			else
				break ;
		}
		if (token->type & OPERATOR && ft_strncmp(token->content, "|", 1) == 0)
		{
			add_command_back(&command_list, new_command_node(D_PIPE, NULL));
			if (!token->next)
				return (syntax_error(&command_list, NULL));
		}
		token = token->next;
	}
	return (command_list);
}
