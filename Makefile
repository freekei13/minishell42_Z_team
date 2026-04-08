NAME = minishell
CC = cc -g
FLAGS = -Wall -Werror -Wextra

SRC_PATH = lexer/
OBJ_PATH = obj/

SRC = main.c lst_tokens.c lexing.c quotes.c
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
INC = -I ./includes/

LIBFT_PATH = libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)
GNL_PATH = gnl/
GNL = $(addprefix $(GNL_PATH), gnl.a)

all: $(NAME)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	$(CC) $(FLAGS) $^ -lreadline -o $@

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