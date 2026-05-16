NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJ_DIR = coders/obj
INC_DIR = coders/inc
SRC_DIR = coders/src

SRC = main.c parse.c context.c time_utils.c dongle.c \
      p_queue.c p_queue_utils.c coder_routine.c coder_init.c coder_utils.c \
      scheduler.c logger.c monitor.c context_init.c dongle_init.c

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS += -I $(INC_DIR)

CODERS    ?= 4
BURNOUT   ?= 1000
COMPILE   ?= 200
DEBUG     ?= 100
REFACTOR  ?= 100
DONGLE    ?= 200
COMPILES  ?= 3
SCHEDULER ?= edf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: coders/src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

normi:
	norminette

run: $(NAME)
	./$(NAME) --coders $(CODERS) --burnout $(BURNOUT) --compile $(COMPILE) \
	          --debug $(DEBUG) --refactor $(REFACTOR) --dongle $(DONGLE) \
	          --compiles $(COMPILES) --scheduler $(SCHEDULER)

.PHONY: all clean fclean re run normi
