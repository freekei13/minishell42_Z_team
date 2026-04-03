NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra

LEXER_PATH = lexer/
PARSER_PATH = parser/
OBJ_PATH = obj/

SRC_LEXER = main.c lst_tokens.c lexing.c
SRC_PARSER = parsing.c lst_redirects.c tools.c
SRCS = $(addprefix $(LEXER_PATH), $(SRC_LEXER)) $(addprefix $(PARSER_PATH), $(SRC_PARSER))
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