# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 00:41:21 by yonshin           #+#    #+#              #
#    Updated: 2023/02/26 00:41:28 by yonshin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OPTIONS = rc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror $(DEBUG)
OBJECTS = \
	ft_isalnum.o \
	ft_isalpha.o \
	ft_isascii.o \
	ft_isdigit.o \
	ft_isprint.o \
	ft_atoi.o \
	ft_bzero.o \
	ft_calloc.o \
	ft_calloc_guard.o \
	ft_itoa.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_memcpy.o \
	ft_memmove.o \
	ft_memset.o \
	ft_putchar_fd.o \
	ft_putendl_fd.o \
	ft_putnbr_fd.o \
	ft_putstr_fd.o \
	ft_split.o \
	ft_strchr.o \
	ft_strdup.o \
	ft_strjoin.o \
	ft_strlcat.o \
	ft_strlcpy.o \
	ft_strlen.o \
	ft_strmapi.o \
	ft_striteri.o \
	ft_strncmp.o \
	ft_strnstr.o \
	ft_strrchr.o \
	ft_strtrim.o \
	ft_substr.o \
	ft_tolower.o \
	ft_strlower.o \
	ft_toupper.o \
	ft_strupper.o \
	ft_lstnew.o \
	ft_lstnew_guard.o \
	ft_lstadd_front.o \
	ft_lstsize.o \
	ft_lstlast.o \
	ft_lstadd_back.o \
	ft_lstdelone.o \
	ft_lstclear.o \
	ft_lstiter.o \
	ft_lstmap.o \
	get_next_line.o \
	get_next_line_utils.o \
	ft_malloc_guard.o \
	ft_strjoin_guard.o \
	ft_substr_guard.o \
	ft_strdup_guard.o \
	ft_iscontain.o \
	intdup.o \
	ft_putstr_fd_line.o \

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
