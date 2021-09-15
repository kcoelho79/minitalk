# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kde-oliv <kde-oliv@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 19:38:04 by kde-oliv          #+#    #+#              #
#    Updated: 2021/09/14 19:38:51 by kde-oliv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: server client

server: server.o libft
	gcc -o server server.o -Llibft -lft

client: client.o libft
	gcc -o client client.o -Llibft -lft

%.o: %.c
	gcc -c -Wall -Wextra -Werror $?

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f server client libft/libft.a

re: fclean all

.PHONY: all libft clean fclean re