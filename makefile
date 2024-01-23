# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 13:34:58 by muel-bak          #+#    #+#              #
#    Updated: 2024/01/22 22:55:36 by muel-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -g 

SRC = ./input/ft_atoi.c ./input/ft_isdigit.c ./input/error.c\
	  ./philo_utils/init.c ./philo_utils/philos.c ./philo_utils/helping_utils.c

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)
MAIN = philo_main.c
NAME = philo

all: $(NAME) clean
$(NAME): $(OBJ) philo.h
	@echo "\033[1;32mMaking philo...\x1b[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -fsanitize=thread
	@echo "\033[1;32mphilo is ready to be used\033[1;36m ※\(^o^)/※"
%.o:%.c philo.h
	@$(CC) $(FLAGS) -c $< -o $@ -fsanitize=thread
clean:
	@echo "\033[1;32mCleaning object files..."
	@rm -f $(OBJ)
	@echo "\033[1;32mDone!"
fclean:
	@echo "\033[1;32mCleaning Everything..."
	@rm -f $(NAME)
	@rm -f $(OBJ)
	@echo "\033[1;32mDone!"
re: fclean all

.PHONY: all clean fclean re bonus