NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJ_DIR = obj
INC_DIR = inc

SRC = src/main.c src/parse.c
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CFLAGS += -I $(INC_DIR)

CODERS    ?= 1
BURNOUT   ?= 2
COMPILE   ?= 3
DEBUG     ?= 4
REFACTOR  ?= 5
DONGLE    ?= 228
COMPILES  ?= 9
SCHEDULER ?= FIFO

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

normi:
	norminette

run: $(NAME)
	./$(NAME) --coders $(CODERS) --burnout $(BURNOUT) --compile $(COMPILE) \
               --debug $(DEBUG) --refactor $(REFACTOR) --dongle $(DONGLE) \
               --compiles $(COMPILES) --scheduler $(SCHEDULER)

.PHONY: all clean fclean re run