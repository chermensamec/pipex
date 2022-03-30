NAME = pipex_m
BONUS = pipex
SRC =  ft_split.c ft_strlen.c ft_strjoin.c ft_strnstr.c\
       ft_strlcpy.c main.c pipex_utils.c ft_strdup.c

SRC_BONUS = main_bonus.c read_from_terminal.c ft_split.c\
	ft_strlen.c ft_strjoin.c ft_strncmp.c ft_strlcpy.c\
	ft_strdup.c get_next_line.c pipex_utils.c ft_strnstr.c\
	ft_strchr.c

CC = gcc

CFLAGS = #-Wall -Wextra -Werror

OBJ = $(patsubst %.c,%.o,$(SRC))

OBJ_BONUS = $(patsubst %.c,%.o,$(SRC_BONUS))

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS) : $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS)

%.o : %.c pipex.h pipex_bonus.h
	gcc $(CFLAGS) -c $< -o $@ -g

clean :
	rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -f $(NAME) $(BONUS)

re : fclean all

