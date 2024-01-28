# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 13:34:58 by muel-bak          #+#    #+#              #
#    Updated: 2024/01/28 08:00:38 by muel-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror

SRC = ./input/ft_atoi.c ./input/ft_isdigit.c ./input/error.c\
	  ./philo_utils/init.c ./philo_utils/philos.c ./philo_utils/helping_utils.c\
	  ./philo_utils/sudo.c

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)
MAIN = philo_main.c
NAME = philo

all: make_msg $(NAME)

make_msg:
	@echo "\033[1;36m \n"
	@echo "██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝"
	@echo "\033[1;32m\nMaking philo...\x1b[0m"

clean_msg:
	@echo "\033[1;32mCleaning object files..."

fclean_msg:
	@echo "\033[1;32mCleaning Everything..."

$(NAME): $(OBJ) philo.h
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "\033[1;32mphilo is ready to be used\033[1;36m ※\(^o^)/※"

%.o:%.c philo.h
	@$(CC) $(FLAGS) -c $< -o $@

clean: clean_msg
	@rm -f $(OBJ)
	@echo "\033[1;32mDone!"

fclean: fclean_msg
	@rm -f $(NAME)
	@rm -f $(OBJ)
	@echo "\033[1;32mDone!"

re: fclean all

.PHONY: all clean fclean re bonus pre_message
