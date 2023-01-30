# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 20:46:00 by yonshin           #+#    #+#              #
#    Updated: 2023/01/31 18:50:20 by juykang          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell
ifdef DEBUG
	CFLAGS = -Wall -Wextra
else
	CFLAGS = -Wall -Wextra -Werror
endif
LIB = \
	./lib/libft/libft.a \

INCLUDE = $(addprefix -I, $(dir $(LIB)))
LIBDUP = $(notdir $(LIB))
OBJS = \
	minishell.o \
	data.o \
	execute.o \
	expanding.o \
	init_signal.o \
	init_envp.o \
	parse.o \

ifdef WITH_BONUS
	OBJS = $(BONUS_OBJS)
endif

all: $(NAME) 

bonus:
	make WITH_BONUS=1 all

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBDUP) $(DEBUG) $(OUTPUT_OPTION) -lreadline

$(LIB):
	make -C $(@D)
	cp $@ $(@F)

%.o: %.c $(LIB)
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) $(INCLUDE) $(DEBUG) -c $*.c

clean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)
	for dir in $(dir $(LIB)); do make -C $$dir clean; done

fclean: clean
	rm -f $(NAME)
	for dir in $(dir $(LIB)); do make -C $$dir fclean; done
	rm -f $(LIBDUP)

re: 
	make fclean
	make all

dev:
	if [ -e $(NAME) ]; then make fclean; fi
	make all
	./$(NAME)

debug:
	make DEBUG='-g3 -fsanitize=address'

test: debug
	./$(NAME)

.PHONY : all clean fclean re bonus debug dev test
