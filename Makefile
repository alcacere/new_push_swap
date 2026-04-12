NAME        = push_swapi
BONUS_NAME  = checker

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -rf
i
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
BONUS_DIR   = bonus
LIBFT_DIR   = libft

# Libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Includes
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)

# .c of the mail program
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
              algorithms/algo_simple.c \
              algorithms/algo_medium.c \
              algorithms/algo_complex.c \
              algorithms/costs.c

# .c bonus files
BONUS_FILES = $(filter-out main.c, $(SRC_FILES)) \
              ../$(BONUS_DIR)/checker_main.c \
              ../$(BONUS_DIR)/checker_utils.c

# .o files
OBJ_FILES   = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
BONUS_OBJS  = $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))


# Rules
all: $(LIBFT) $(NAME)

# Libft compilation
$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

# Main executable file compilation
$(NAME): $(OBJ_FILES)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "¡$(NAME) compiled successfully!"

# .o files compilation pattern and subdirectories creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling $<"

# Bonus rule
bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "¡$(BONUS_NAME) compiled successfully!"

# .o cleanup
clean:
	@echo "Cleaning .o files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

# .o + executables cleanup
fclean: clean
	@echo "Cleaning executables..."
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

# Recompiling
re: fclean all

.PHONY: all clean fclean re bonus
