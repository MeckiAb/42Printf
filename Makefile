NAME = libftprintf.a
CC = cc -Wall -Wextra -Werror
AR = ar -csr

SRC = ft_printf.c

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $?

%.o : %.c
	$(CC) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re