# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/21 13:59:42 by pmolnar       #+#    #+#                  #
#    Updated: 2023/03/15 16:47:00 by jzaremba      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
LDFLAGS			=	-L$(shell brew --prefix readline)/lib
CFLAGS			+=	-g # debug
CFLAGS			+=	-fsanitize=address
NAME			=	minishell
INCL			=	inc libft/inc
SUBMODULE		=	libft
LIBFT			=	$(SUBMODULE)/libft.a


# PARSER
CHAR_READER		=	$(addprefix	character_reader/, character_reader.c)

TOKENIZER		=	$(addprefix	tokenizer/,	tokenizer.c				\
											token_classifier.c)

EXPANDER 		=	$(addprefix	expander/,	expander.c				\
											expander_util.c)
											
VAR_INTERPRETER	=	$(addprefix	variable_parser/,	variable_parser.c	\
													variable_parser_util.c)

CMD_PARSER		=	$(addprefix	command_list/,	parse_commands.c	\
												parse_operators.c)
EXECUTE			=	$(addprefix executor/,		executor.c		\
												exec_commands.c \
												exec_utils.c	\
												redirect.c)

PARSER			=	$(addprefix parser/,	$(CHAR_READER)		\
											$(TOKENIZER)		\
											$(CMD_PARSER)	\
											$(EXPANDER)			\
											$(VAR_INTERPRETER))

# SIGNAL HANDLER
SIGNAL			=	$(addprefix signal/, $(SIG_HANDLER))

SIG_HANDLER		=	$(addprefix	signal/, signal_handler.c)

# BUILTINS
EXPORT			=	$(addprefix export/,	export.c)
ENV				=	$(addprefix env/, env.c)
UNSET			=	$(addprefix unset/,		unset.c)
PWD				=	$(addprefix pwd/,		pwd.c)
ECHO			=	$(addprefix echo/,		echo.c)

BUILTIN			=	$(addprefix builtin/, 	$(EXPORT)			\
											$(UNSET)			\
											$(PWD)				\
											$(ENV)				\
											$(ECHO)				\
													)

PARSER_PATH		=	parser/
SIG_PATH		=	signal/
EXEC_PATH		=	executor/

PARSER			=	$(addprefix $(PARSER_PATH), $(CHAR_READER)		\
												$(TOKENIZER)		\
												$(CMD_PARSER)		\
												$(EXPANDER)			\
												$(VAR_INTERPRETER))
SIGNAL			=	$(addprefix $(SIG_PATH), $(SIG_HANDLER))
EXECUTOR		=	$(addprefix $(EXEC_PATH), $(EXECUTE))

# UTILS
UTIL_PATH		=	util/
UTIL			=	$(addprefix $(UTIL_PATH), 	token_list_util.c	\
												command_list_util.c)

# ALL SOURCE FILES
SRC				=	main.c $(PARSER) $(UTIL) $(SIGNAL) $(BUILTIN) $(EXECUTOR)

OBJ_PATH		=	obj/
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))


all:	$(NAME)
	@printf "All compiled into '$(NAME)' executable\n"

$(NAME):	$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -lreadline $^ -o $(NAME)

$(LIBFT): $(SUBMODULE)
	git submodule update --init
	make -C $(SUBMODULE)

$(SUBMODULE):
	git submodule init $(SUBMODULE)

$(OBJ_PATH)%.o:	src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@ 

clean:
	rm -rf $(OBJ_PATH)
	make clean -C $(SUBMODULE)

fclean:	clean
	rm $(NAME)
	make fclean -C $(SUBMODULE)

re: fclean all

.PHONY: all clean fclean re 