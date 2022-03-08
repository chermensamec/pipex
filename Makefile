NAME = pipex
SRC =  ft_split.c ft_strlen.c ft_strjoin.c ft_strnstr.c\
       ft_strlcpy.c main.c pipex_utils.c

CC = gcc

CFLAGS = #-Wall -Wextra -Werror

OBJ = $(patsubst %.c,%.o,$(SRC))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c pipex.h
	gcc $(CFLAGS) -c $< -o $@ -g

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

