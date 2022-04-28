# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwane <mwane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 13:49:19 by truepath          #+#    #+#              #
#    Updated: 2022/04/26 16:55:38 by mwane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 	= philo_one.c utils.c utils_arg.c work_fonctions.c

FLAGS 	= -Wall -Werror -Wextra -pthread

CC	 	= gcc

OBJ		= $(SRCS:.c=.o)

NAME	= philosopher


all :	$(NAME)

$(NAME) :	$(OBJ)
			$(CC) -o $(NAME) $(FLAGS) $(OBJ)

clean	:
			rm -rf $(OBJ)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o 	:	%.c
			$(CC) $(FLAGS) -o $@ -c $<