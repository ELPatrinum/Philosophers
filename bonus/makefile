# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 11:01:14 by muel-bak          #+#    #+#              #
#    Updated: 2024/01/28 11:04:06 by muel-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./philo_bonus

FLAGS = -Wall -Wextra -Werror
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


SRC_FILES = main_bonus.c philo.c utils.c init.c error.c ft_atoi.c ft_isdigit.c


OBJS := $(SRC_FILES:.c=.o)

CC = cc


all: make_msg $(NAME)

make_msg:
	@echo "\033[1;36m \n"
	@echo "██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ BONUS"
	@echo "\033[1;32m\nMaking philo...\x1b[0m"

clean_msg:
	@echo "\033[1;32mCleaning object files..."

fclean_msg:
	@echo "\033[1;32mCleaning Everything..."

$(NAME): $(OBJS) philo.h
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "\033[1;32mphilo is ready to be used\033[1;36m ※\(^o^)/※"

%.o:%.c philo.h
	@$(CC) $(FLAGS) -c $< -o $@

clean: clean_msg
	@rm -f $(OBJS)
	@echo "\033[1;32mDone!"


fclean: fclean_msg
	@rm -f $(NAME)
	@rm -f $(OBJS)
	@echo "\033[1;32mDone!"

re: fclean all

.PHONY: all clean fclean re
