# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 10:07:26 by jhapke            #+#    #+#              #
#    Updated: 2025/05/14 11:15:07 by jhapke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

DIR_SRC = src
DIR_CORE = $(DIR_SRC)/core
DIR_UTILS = $(DIR_SRC)/utils
DIR_INC = include

SOURCE = 	$(DIR_SRC)/main.c\
			$(DIR_CORE)/cleanup.c\
			$(DIR_CORE)/init.c\
			$(DIR_CORE)/monitor.c\
			$(DIR_CORE)/routine.c\
			$(DIR_CORE)/threads.c\
			$(DIR_CORE)/time.c\
			$(DIR_UTILS)/utils.c

OBJS = $(SOURCE:.c=.o)

FLAGS = -Werror -Wextra -Wall

CC = gcc

HEADER = $(DIR_INC)/philo.h

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -I$(DIR_INC) -c $< -o $@

clean:
		rm -rf $(OBJS)
fclean: clean
		rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re