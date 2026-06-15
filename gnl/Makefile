NAME = gnl.a
SRC = get_next_line.c
OBJ = $(SRC:.c=.o)

AR = ar rcs
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

LIBFT_PATH = ../libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

all: $(NAME)

$(NAME):$(OBJ)
	$(AR) $@ $^

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all