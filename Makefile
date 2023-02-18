NAME = minishell
.DEFAULT_GOAL = all

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
CFLAGS = -Wall -Wextra
LDFLAGS = -L$(shell brew --prefix readline)/lib
ifndef DEBUG
	CFLAGS += -Werror
else
	CFLAGS += $(DEBUG)
endif

LIB = \
	$(LIB_DIR)/libft/libft.a \
	$(LIB_DIR)/libstr/libstr.a \

INCLUDE = $(addprefix -I, $(dir $(LIB)))

HEADER = $(shell find $(SRC_DIR) -name "*.h" -type f)
INCLUDE += $(addprefix -I, $(dir $(HEADER)))
SRC = $(shell find $(SRC_DIR) -name "*.c" -type f)
OBJ = $(foreach path,$(SRC:.c=.o),$(shell sed "s/^$(SRC_DIR)/$(OBJ_DIR)/g"<<<$(path)))

.PHONY: all clean fclean re bonus debug dev test

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OUTPUT_OPTION) $(OBJ) $(LIB) -lreadline

$(LIB):
	make -C $(@D)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) $(INCLUDE) $(DEBUG) -c $<

clean:
	for dir in $(dir $(LIB)); do make -C $$dir clean; done
	rm -rf $(OBJ_DIR)

fclean: clean
	for dir in $(dir $(LIB)); do make -C $$dir fclean; done
	rm -f $(NAME)

re: fclean
	make all

debug:
	make DEBUG='-g3'

test: debug
	./$(NAME)
