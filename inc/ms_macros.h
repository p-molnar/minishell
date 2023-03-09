/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_macros.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 14:13:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/03/09 14:29:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MACROS_H
# define MS_MACROS_H

//	unrequired operators
// # define AND '&'
// # define SEMI ';'
// # define LPAREN '('
// # define RPAREN ')'
// # define BACKQUOTE '`'
// # define BACKSLASH '\\'

//	collections
# define META_CHARS " \t\n|&;()<>"
# define OPERATORS "|&;()<>"
# define SPACES	" \t\n"
# define QUOTES "'\""
# define DELIM_CHARS " \t\n|&;()<>'\""

//	argument symbol
# define DASH '-'

//	variable definition
# define EQUAL '='

// operator symbols
# define PIPE '|'
# define LESS '<'
# define DLESS "<<"
# define GREAT '>'
# define DGREAT ">>"
# define DOLLAR '$'
# define DQUOTE '"'
# define QUOTE '\''
# define SPACE ' ' 
# define TAB '\t'
# define NEWLINE '\n'

//	token type classifiers
enum e_token_type {
	UNDEFINED = -1,
	INVALID,
	WORD,
	OPERATOR,
};

//	command list symbols
enum	e_command_symbol
{
	CMD,
	ARG,
	ASSIGNMENT,
	OUTFILE,
	OUTFILE_APP,
	INFILE,
	D_PIPE,
};

#endif
