NAME := cub3d
CFLAGS := -Wextra -Wall -Werror
CFLAGS += -g3
JOBS := -j50
MAKEFLAGS += --no-print-directory
YELLOW := $(shell tput setaf 3)
GREEN := $(shell tput setaf 2)
RESET := $(shell tput sgr0)

CC := cc
RM := rm -rf

LIBS := -lmlx -lXext -lX11 -lm

OBJ_DIR := build

SRCS := cub3d.c player_movement.c clear_display.c map.c rays.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

bonus: $(NAME)_bonus

print_start:
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): print_start $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@$(RM) $(NAME) build

re: fclean all


.PHONY: all clean fclean re
