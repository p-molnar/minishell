# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/20 14:03:39 by pmolnar       #+#    #+#                  #
#    Updated: 2023/02/20 14:33: by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra

NAME			=	minishell
INCL			=	includes
SRC_NAMES		=	main
SRC				=	$(addsuffix .c, $(SRC_NAMES))
OBJ_PATH		=	obj/
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))

# $@ target
# $^ all prereq

all:	$(NAME)
	@printf "All compiled into '$(NAME)' executable\n"

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -lreadline $^ -o $(NAME)

$(OBJ_PATH)%.o:	src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean:	clean
	rm $(NAME)

re: clean all

.PHONY: all clean fclean re 