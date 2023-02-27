# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/21 13:59:42 by pmolnar       #+#    #+#                  #
#    Updated: 2023/02/27 16:16:20 by jzaremba      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
NAME			=	minishell
INCL			=	includes $(SUBMODULE)/include
SUBMODULE		=	libft
LIBFT			=	$(SUBMODULE)/libft.a
LDFLAGS			=	-L/Users/$(USER)/.brew/opt/readline/lib

CHAR_READER		=	$(addprefix	character_reader/, character_reader.c)
SIG_HANDLER		=	$(addprefix	signal/, signal_handler.c)
 
PARSER_PATH		=	parser/
SIG_PATH		=	signal/
PARSER			=	$(addprefix $(PARSER_PATH), $(CHAR_READER))
SIGNAL			=	$(addprefix $(SIG_PATH), $(SIG_HANDLER))
SRC				=	main.c $(PARSER) $(SIGNAL)

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