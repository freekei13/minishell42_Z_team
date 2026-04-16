NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra

LEXER_PATH	=	lexer/
PARSER_PATH	=	parser/
EXECUTER_PATH	=	executer/
BUILTIN_PATH	=	Built-in/
ENVP_PATH	=	envp/
OBJ_PATH	=	obj/

SRC_LEXER	=	main.c lst_tokens.c lexing.c \
				dequote.c quotes.c
SRC_PARSER	=	parsing.c lst_redirects.c tools_parse.c
SRC_EXECUTER =	executing.c path.c redirects_exec.c \
				tools_exec.c cmd_exec.c pipe_exec.c
SRC_BUILTIN	=	built-in.c cd_bi.c echo_bi.c env_bi.c \
				exit_bi.c export_bi.c pwd_bi.c unset_bi.c
SCR_ENVP	=	envp.c env_remake.c env_remake_b.c
SRCS = 	$(addprefix $(LEXER_PATH), $(SRC_LEXER)) \
		$(addprefix $(PARSER_PATH), $(SRC_PARSER)) \
		$(addprefix $(EXECUTER_PATH), $(SRC_EXECUTER)) \
		$(addprefix $(BUILTIN_PATH), $(SRC_BUILTIN)) \
		$(addprefix $(ENVP_PATH), $(SCR_ENVP))
OBJ = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(notdir $(OBJ)))
INC = -I ./includes/

LIBFT_PATH = libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)
GNL_PATH = gnl/
GNL = $(addprefix $(GNL_PATH), gnl.a)

all: $(NAME)

$(OBJ_PATH)%.o:$(LEXER_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ -g

$(OBJ_PATH)%.o:$(PARSER_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ -g

$(OBJ_PATH)%.o:$(EXECUTER_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ -g

$(OBJ_PATH)%.o:$(BUILTIN_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ -g

$(OBJ_PATH)%.o:$(ENVP_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ -g

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	$(CC) $(FLAGS) $^ -lreadline -o $@ -g

$(LIBFT):
	make -C $(LIBFT_PATH)

$(GNL):
	make -C $(GNL_PATH)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_PATH)
	make clean -C $(GNL_PATH)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)
	make fclean -C $(GNL_PATH)

re: fclean all