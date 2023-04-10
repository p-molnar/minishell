/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_macros.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 14:13:40 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/10 12:19:58 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MACROS_H
# define MS_MACROS_H

//	command parser returns
# define RET_END 0
# define RET_PIPE 1
# define RET_SYNTAX_ERR 2

//	unrequired operators
// # define AND '&'
// # define SEMI ';'
// # define LPAREN '('
// # define RPAREN ')'
// # define BACKQUOTE '`'
// # define BACKSLASH '\\'

//	collections
# define OPERATORS "|<>"
# define SPACES	" \t\n"
# define QUOTES "'\"" // QUOTE and DQUOTE
# define DELIM_CHARS " \t\n|<>"

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

//	exit/return methods of error function
enum e_var_type{
	UNDEF = 0,
	ENV = 1 << 0,
	SHL = 1 << 1,
};

//	token type classifiers
enum e_token_type {
	UNDEFINED = 0,
	INVALID = 1 << 1,
	WORD = 1 << 2,
	OPERATOR = 1 << 3,
	S_QUOTED = 1 << 4,
	D_QUOTED = 1 << 5,
};

//	exit/return methods of error function
enum e_exit_methods {
	EXIT = 1,
	RETURN = 2,
	PRINT = 3,
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
	HEREDOC_DELIMITER,
	D_PIPE,
};

enum	e_env_var {
	HOME,
	PWD,
	OLDPWD,
	ITERABLE_PATH,
	ENV_SIZE
};

#endif
