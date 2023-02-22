# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/21 13:59:42 by pmolnar       #+#    #+#                  #
#    Updated: 2023/02/22 14:03:02 by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
NAME			=	minishell
INCL			=	includes libft/include
SUBMODULE		=	libft
LIBFT			=	$(SUBMODULE)/libft.a

CHAR_READER		=	$(addprefix	character_reader/, character_reader.c)
TOKENIZER		=	$(addprefix	tokenizer/, tokenizer.c)

TOKENIZER_PATH	=	tokenizer/
PARSER_PATH		=	parser/

PARSER			=	$(addprefix $(PARSER_PATH), $(CHAR_READER) \
												$(TOKENIZER))

SRC				=	main.c $(PARSER)

OBJ_PATH		=	obj/
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))


all:	$(NAME)
	@printf "All compiled into '$(NAME)' executable\n"

$(NAME):	$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -lreadline $^ -o $(NAME)

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