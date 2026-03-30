NAME = gnl.a
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

AR = ar rcs
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

all: $(NAME)

$(NAME):$(OBJ)
	$(AR) $@ $^

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all