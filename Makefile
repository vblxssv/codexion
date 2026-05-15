NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJ_DIR = obj
INC_DIR = inc

SRC = src/main.c src/parse.c src/context.c src/time_utils.c src/dongle.c \
 src/p_queue.c src/p_queue_utils.c src/coder_routine.c src/coder_init.c src/coder_utils.c \
 src/scheduler.c src/logger.c src/monitor.c src/context_init.c src/dongle_init.c

OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CFLAGS += -I $(INC_DIR)

CODERS    ?= 3
BURNOUT   ?= 1000
COMPILE   ?= 200
DEBUG     ?= 100
REFACTOR  ?= 100
DONGLE    ?= 100
COMPILES  ?= 5
SCHEDULER ?= fifo

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