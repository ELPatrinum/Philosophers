# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 13:34:58 by muel-bak          #+#    #+#              #
#    Updated: 2024/01/18 17:13:42 by muel-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

SRC = ./input/ft_atoi.c ./input/ft_isdigit.c ./input/error.c\
	  ./philo_utils/init.c

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)
MAIN = philo_main.c
NAME = Philosophers

all: $(NAME) clean
$(NAME): $(OBJ) philo.h
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
%.o:%.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus