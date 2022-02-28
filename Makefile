# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 01:49:00 by fcavillo          #+#    #+#              #
#    Updated: 2022/02/28 16:48:24 by fcavillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

CC	= clang++

CFLAGS	= -Wall -Wextra -Werror -std=c++98

#SRCS =	main.cpp 
SRCS =	speedtest.cpp

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}: $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all : ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY:	all clean re fclean re