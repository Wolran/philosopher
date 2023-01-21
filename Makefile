# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmuller <vmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 04:19:36 by vmuller           #+#    #+#              #
#    Updated: 2023/01/21 15:41:10 by vmuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g3

SRC			= 	srcs/init.c srcs/main.c srcs/operations.c \
				srcs/checker.c srcs/utils.c \

OBJECT		= ${SRC:.c=.o}
INC			= includes

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INC}

${NAME} : ${OBJECT}
	${CC} ${OBJECT} -o ${NAME} 

all : ${NAME}

clean :
	rm -f ${OBJECT}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re
