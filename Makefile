NAME        = push_swap
BONUS_NAME  = checker

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -rf

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
BONUS_DIR   = bonus
LIBFT_DIR   = libft

LIBFT       = $(LIBFT_DIR)/libft.a

INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)

SRC_FILES   = main.c \
              setup/parsing.c \
              setup/flags.c \
              setup/stack_utils.c \
              setup/stack_init.c \
              setup/memory.c \
              operations/push.c \
              operations/swap.c \
              operations/rotate.c \
              operations/rev_rotate.c \
              operations/output.c \
              operations/output_bench.c \
              algorithms/metrics.c \
              algorithms/simple.c \
              algorithms/medium.c \
              algorithms/complex.c \
              algorithms/quicksort_cases_a.c \
              algorithms/quicksort_cases_b.c \
              algorithms/complex_utils.c

BONUS_SRC   = checker_main.c \
              checker_utils.c

OBJ_FILES   = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
BONUS_OBJS  = $(filter-out $(OBJ_DIR)/main.o, $(OBJ_FILES)) \
              $(addprefix $(OBJ_DIR)/$(BONUS_DIR)/, $(BONUS_SRC:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling $<"

$(OBJ_DIR)/$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling bonus $<"

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "$(BONUS_NAME) compiled successfully!"

clean:
	@echo "Cleaning .o files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning executables..."
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
