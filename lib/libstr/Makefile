# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:29:59 by yonshin           #+#    #+#              #
#    Updated: 2023/02/26 00:39:35 by yonshin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPTIONS = rc
NAME = libstr.a
CFLAGS = -Wall -Wextra -Werror $(DEBUG)
INCLUDE = -I../libft/
OBJECTS = \
	strb_init.o \
	strb_add_front.o \
	strb_add_back.o \
	strb_clear.o \
	strb_build.o \
	str_concat.o \

$(NAME): $(OBJECTS)
	ar $(OPTIONS) $@ $^

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(OUTPUT_OPTION) $(DEBUG) -c $*.c

.PHONY: all bonus clean fclean re
