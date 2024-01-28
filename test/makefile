NAME = ./philo_bonus


# Project's directories
OBJECTSDIR = objects
HEADERFILE = philosophers.h


# Name of variables
FLAGS = -Wall -Wextra -Werror
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


# philosophers files variable
SRC_FILES = input.c \
philo.c \
utils.c \
init.c \



# Define objects for all sources
OBJS := $(SRC_FILES:.c=.o)

# Name the compiler
CC = gcc

# OS specific part
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
MAKE = make -C


all: $(NAME)


# philosophers making rules
$(NAME): $(OBJS)
	@$(CC) -I $(HEADERFILE) $(OBJS) -o $@

$(OBJECTSDIR)/%.o: %.c $(HEADERFILE)
	@$(CC) $(FLAGS) -I $(HEADERFILE) -o $@ -c $<

# Remove all objects, dependencies and executable files generated during the build
clean:
	@$(RM) $(OBJS)


fclean: clean
	@$(RM) $(NAME) philo_bonus.dSYM $(ERRIGNORE)

re: fclean all