/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_macros.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 14:13:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/02/27 17:20:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MACROS_H
# define MS_MACROS_H

// operator symbols
# define PIPE "|"
# define AND '&'
# define SEMI ';'
# define LESS '<'
# define GREAT '>'
# define LPAREN '('
# define RPAREN ')'
# define DOLLAR '$'
# define BACKQUOTE '`'
# define BACKSLASH '\\'
# define DQUOTE '"'
# define QUOTE '\''
# define SPACE " "
# define TAB '\t'
# define NEWLINE '\n'

# define META_CHARS " \t\n|&;()<>"
# define OPERATORS "|&;()<>"
# define SPACES	" \t\n"

enum e_token_type {
	UNDEFINED = -1,
	WORD = 1,
	OPERATOR = 2,
};

#endif