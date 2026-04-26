NAME        = push_swap
BONUS_NAME  = checker

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -rf

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
BONUS_DIR   = bonus
LIBFT_DIR   = libft
TEST_DIR    = tests

# Libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Includes
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)

# Main program .c files
SRC_FILES   = main.c \
              setup/parsing.c \
              setup/flags.c \
              setup/stack_utils.c \
              setup/memory.c \
              operations/push.c \
              operations/swap.c \
              operations/rotate.c \
              operations/rev_rotate.c \
              operations/output.c \
              algorithms/metrics.c \
              algorithms/simple.c \
              algorithms/medium.c \
              algorithms/complex.c \
              algorithms/costs.c \
			  algorithms/greedy_metrics.c \
			  algorithms/quicksort_helpers.c

# Bonus program .c files
BONUS_FILES = $(filter-out main.c, $(SRC_FILES)) \
              ../$(BONUS_DIR)/checker_main.c \
              ../$(BONUS_DIR)/checker_utils.c

# Object files
OBJ_FILES   = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
BONUS_OBJS  = $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))

all: $(LIBFT) $(NAME)

# Libft compilation
$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

# Main executable compilation
$(NAME): $(OBJ_FILES)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

# Object files compilation pattern and subdirectories creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling $<"

# Bonus rule
bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "$(BONUS_NAME) compiled successfully!"

# Dynamic rule to test modules (e.g., make test-parsing)
test-%: $(LIBFT) $(OBJ_FILES)
	@echo "Compiling test for $*..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(TEST_DIR)/test_$*.c $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES)) $(LIBFT) -o test_$*
	@echo "Test compiled! Executing ./test_$*...\n"
	@./test_$*

# Clean object files
clean:
	@echo "Cleaning .o files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(RM) test_*

# Clean objects and executables
fclean: clean
	@echo "Cleaning executables..."
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

.PHONY: all clean fclean re bonus