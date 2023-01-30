# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:29:59 by yonshin           #+#    #+#              #
#    Updated: 2023/01/26 22:52:07 by yonshin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPTIONS = rc
NAME = libtree.a
CFLAGS = -Wall -Wextra -Werror $(DEBUG)
OBJECTS = \
	delete_child.o \
	free_tree.o \
	free_tree_node.o \
	iterate_tree.o \
	new_tree_node.o \
	get_child.o \
	get_root.o \
	add_tree_node.o \
	add_new_tree_node.o \

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
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) $(DEBUG) -c $*.c

.PHONY: all bonus clean fclean re
