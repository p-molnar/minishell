/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 14:38:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/28 12:09:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ms_data_types.h>

# define PROMPT_MSG "minishell$ "

//	character_reader.c
char			*read_prompt(const char *prompt);

//	tokenizer.c
t_token_list	*tokenizer(const char *prompt);

//	token_list_util.c
t_token_list	*new_node(char *content, int token_type);
void			add_node_last(t_token_list **list, t_token_list *node);
void			free_list(t_token_list *list);

//	token_classifier.c
void	classify_tokens(t_token_list *list);


#endif