# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/21 13:59:42 by pmolnar       #+#    #+#                  #
#    Updated: 2023/03/06 17:11:21 by jzaremba      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
LDFLAGS			=	-L$(shell brew --prefix readline)/lib
# CFLAGS			+=	-g # debug
CFLAGS			+=	-fsanitize=address
NAME			=	minishell
INCL			=	inc libft/inc
SUBMODULE		=	libft
LIBFT			=	$(SUBMODULE)/libft.a

CHAR_READER		=	$(addprefix	character_reader/, character_reader.c)
TOKENIZER		=	$(addprefix	tokenizer/,	tokenizer.c				\
											token_classifier.c)
CMD_PARSER		=	$(addprefix	command_list/,	parse_commands.c	\
												parse_operators.c)

TOKENIZER_PATH	=	tokenizer/
PARSER_PATH		=	parser/
SIG_PATH		=	signal/

PARSER			=	$(addprefix $(PARSER_PATH), $(CHAR_READER) \
												$(TOKENIZER)	\
												$(CMD_PARSER))
SIGNAL			=	$(addprefix $(SIG_PATH), $(SIG_HANDLER))

UTIL_PATH		=	util/
UTIL			=	$(addprefix $(UTIL_PATH), 	token_list_util.c	\
												command_list_util.c)
SIG_HANDLER		=	$(addprefix	signal/, signal_handler.c)

SRC				=	main.c $(PARSER) $(UTIL) $(SIGNAL)

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