# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/21 13:59:42 by pmolnar       #+#    #+#                  #
#    Updated: 2023/04/04 12:28:39 by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
LDFLAGS			=	-L$(shell brew --prefix readline)/lib
CFLAGS			+=	-g # debug
# CFLAGS			+=	-fsanitize=address
NAME			=	minishell
INCL			=	inc libft/inc
SUBMODULE		=	libft
LIBFT			=	$(SUBMODULE)/libft.a

# PRINT FORMATTING
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[1;33m
BOLD			=	\033[1m
DEF				=	\033[0m
SPACE_W 		= 	%-50s
STATUS_W		=	%-10s
STATUS_FMT		=	$(BOLD)$(STATUS_W)$(DEF) $(SPACE_W)

# PARSER
CHAR_READER		=	$(addprefix	character_reader/,							\
						character_reader.c									\
						)									

TOKENIZER		=	$(addprefix	tokenizer/,									\
						tokenizer.c											\
						token_classifier.c									\
						)

EXPANDER 		=	$(addprefix	expander/,									\
						expander.c											\
						expander_util.c										\
						)
											
VAR_INTERPRETER	=	$(addprefix	variable_parser/,							\
						variable_parser.c									\
						variable_parser_util.c								\
						)

CMD_PARSER		=	$(addprefix	command_list/,								\
						parse_commands.c									\
						parse_operators.c									\
						)

PARSER			=	$(addprefix parser/,									\
						$(CHAR_READER)										\
						$(TOKENIZER)										\
						$(CMD_PARSER)										\
						$(EXPANDER)											\
						$(VAR_INTERPRETER)									\
						)

# SIGNAL HANDLER
SIG_HANDLER		=	$(addprefix	signal/,									\
						signal_handler.c									\
						)

SIGNAL			=	$(addprefix signal/,									\
						$(SIG_HANDLER)										\
						)

# EXECUTOR
EXECUTE			=	$(addprefix executor/,									\
						executor.c											\
						exec_commands.c										\
						exec_builtins.c										\
						exec_builtin_utils.c								\
						env_builder.c										\
						exec_utils.c										\
						)

REDIRECT		=	$(addprefix redirect/,									\
						redirect.c											\
						heredoc.c											\
						)

EXECUTOR		=	$(addprefix executor/,									\
						$(EXECUTE)											\
						$(REDIRECT)											\
						)

# BUILTINS
EXPORT			=	$(addprefix export/,									\
						export.c											\
						)
ENV				=	$(addprefix env/,										\
						env.c												\
						)
EXIT			=	$(addprefix exit/,										\
						exit.c												\
						)
UNSET			=	$(addprefix unset/,										\
						unset.c												\
						)
PWD				=	$(addprefix pwd/,										\
						pwd.c												\
						)
ECHO			=	$(addprefix echo/,										\
						echo.c												\
						)
CD				=	$(addprefix cd/,										\
						cd.c												\
						cd_utils.c											\
						update_working_dirs.c								\
						$(CD_STEPS)											\
						)

CD_STEPS		=	$(addprefix	cd_execution_steps/,						\
						step_1_2.c											\
						step_3.c											\
						step_4.c											\
						step_5.c											\
						step_6.c											\
						step_7.c											\
						step_8.c											\
						step_8_utils.c										\
						)


BUILTIN			=	$(addprefix builtin/,									\
						$(EXPORT)											\
						$(UNSET)											\
						$(PWD)												\
						$(ENV)												\
						$(EXIT)												\
						$(ECHO)												\
						$(CD)												\
						)

# UTILS
UTIL_PATH		=	util/
UTIL			=	$(addprefix $(UTIL_PATH),								\
						token_list_util.c									\
						command_list_util.c									\
						free_objects.c										\
						list_util.c											\
						)

ERROR			=	$(addprefix error/,										\
						error.c												\
						)

# ALL SOURCE FILES
SRC				=	main.c $(PARSER) $(UTIL) $(SIGNAL) $(BUILTIN) $(EXECUTOR) $(ERROR)

OBJ_PATH		=	obj/
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))


all:	$(NAME)
	@printf "$(GREEN)$(NAME) is created at $(shell pwd)$(DEF)\n"

$(NAME):	$(LIBFT) $(OBJ)
	@printf "$(STATUS_FMT)" "building" "$(NAME)"
	@$(CC) $(CFLAGS) $(LDFLAGS) -lreadline $^ -o $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(LIBFT): $(SUBMODULE)
	git submodule update --init
	make -C $(SUBMODULE)

$(SUBMODULE):
	git submodule init $(SUBMODULE)

$(OBJ_PATH)%.o:	src/%.c
	@mkdir -p $(dir $@)
	@printf "$(STATUS_FMT)" "building" "$<"
	@$(CC) $(CFLAGS) -c $^ -o $@ 
	@printf "[$(GREEN)DONE$(DEF)]\n"

clean:
	rm -rf $(OBJ_PATH)
	make clean -C $(SUBMODULE)

fclean:	clean
	rm $(NAME)
	make fclean -C $(SUBMODULE)

re: fclean all

.PHONY: all clean fclean re 