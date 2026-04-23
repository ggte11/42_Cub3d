NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -O3 -march=native -flto -ftree-vectorize -funroll-loops -ffast-math
OBJ_DIR     = obj
MLX_DIR     = minilibx-linux
LIBFT_DIR   = libft
GNL_DIR		= $(LIBFT_DIR)/get_next_line
MLX         = $(MLX_DIR)/libmlx.a
LIBFT       = $(LIBFT_DIR)/libft.a
GNL			= $(GNL_DIR)/get_next_line.a
INCLUDES    = -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)
LIBS        = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -L$(GNL_DIR) -lft -lXext -lX11 -lm
#LIBS        = -L$(MLX_DIR) -L$(LIBFT_DIR) -L$(GNL_DIR) -lft -lXext -lX11 -lm

SRCS		  = cub3d.c \
			  init.c \
			  parsing/file_validation.c \
			  parsing/file_parsing.c \
			  parsing/parse_utils.c \
			  parsing/parse_utils2.c \
			  parsing/normalize_map.c \
			  parsing/validate_map.c \
			  srcs/initializer.c \
			  srcs/player.c srcs/keys.c \
			  srcs/player_utils.c \
			  srcs/free_hub.c \
			  srcs/textures.c \
			  srcs/minimap.c \
			  srcs/wall_col.c \
			  srcs/draw_lines.c \
			  srcs/draw.c \
			  srcs/raycast.c

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
BLUE        = \033[0;34m
CYAN        = \033[0;36m
RESET       = \033[0m

#all: $(LIBFT) $(GNL) $(NAME)
all: $(LIBFT) $(GNL) $(MLX) $(NAME)

$(MLX):
	@echo "$(CYAN)🔨 Building minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@echo "$(CYAN)🔨 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/srcs

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(CYAN)🔨 Compiling $(YELLOW)$<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) created successfully!$(RESET)"

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		echo "$(RED)🗑️  Removing object files...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "$(GREEN)✨ Object files cleaned!$(RESET)"; \
	fi
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@if [ -f $(NAME) ]; then \
		echo "$(RED)💥 Removing $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✨ $(NAME) removed!$(RESET)"; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re