# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/06 05:55:59 by joaolive          #+#    #+#              #
#    Updated: 2026/01/31 18:31:25 by joaolive         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# It detects the number of processors
# (nproc on Linux) and automatically sets the -j option.
ifeq ($(MAKELEVEL),0)
	MAKEFLAGS += -j$(shell nproc)
endif

NAME = cub3d
EXEC = $(BIN_DIR)/$(NAME)

# Colors
CC_GREEN    = \033[38;2;80;250;123m
CC_PINK     = \033[38;2;255;121;198m
CC_BLUE     = \033[38;2;139;233;253m
CC_YELLOW   = \033[38;2;241;250;140m
CC_PURPLE   = \033[38;2;189;147;249m
CC_RED      = \033[38;2;255;85;85m
RESET       = \033[0m

# Tools
CC = cc
AR = ar rcs
RM = rm -rf

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIBFT_DIR = lib/libft
MLX_DIR = lib/mlx
MLX_BUILD  = $(MLX_DIR)/build

# Libraries Paths
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_BUILD)/libmlx42.a

# Flags and Includes
CCFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MMD -MP
CPPFLAGS = -Iinclude -I$(LIBFT_DIR)/include -I$(MLX_DIR)/include

# Libft and MLX
LDFLAGS = -L$(LIBFT_DIR) -L$(MLX_BUILD)
LDLIBS = -lft -lmlx42 -lglfw -lpng16 -ldl -pthread -lm

SRC_MAIN = main mock_map
SRC_CORE = init_window game_loop
SRC_RAYCAST = raycast calculate_batch render_batch render_bg
SRC_INPUTS = key_handler player_controls hook_player
SRC_PLAYER = render_player
SRC_UTILS = apply_wall_shading apply_depth_shading lerp load_image
SRC_PARSING = parser parse_utils map_validators

# Source files
SRC = \
	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_MAIN))) \
	$(addprefix $(SRC_DIR)/core/, $(addsuffix .c, $(SRC_CORE))) \
	$(addprefix $(SRC_DIR)/raycast/, $(addsuffix .c, $(SRC_RAYCAST))) \
	$(addprefix $(SRC_DIR)/inputs/, $(addsuffix .c, $(SRC_INPUTS))) \
	$(addprefix $(SRC_DIR)/player/, $(addsuffix .c, $(SRC_PLAYER))) \
	$(addprefix $(SRC_DIR)/utils/, $(addsuffix .c, $(SRC_UTILS))) \
	$(addprefix $(SRC_DIR)/parsing/, $(addsuffix .c, $(SRC_PARSING)))

# Object files
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Dependencies
DEPS = $(SRC_OBJS:.o=.d)

all: $(LIBFT) $(MLX_LIB) $(EXEC)

$(EXEC): $(SRC_OBJS) | $(BIN_DIR)
	@printf "$(CC_PINK)Linking $(NAME)... $(RESET)"
# Start of Animation Loop
	@for i in 1 2 3 4 5 6 7 8 9 10; do \
		printf "\b\b $(CC_BLUE)| $(RESET)"; sleep 0.05; \
		printf "\b\b $(CC_BLUE)/ $(RESET)"; sleep 0.05; \
		printf "\b\b $(CC_BLUE)- $(RESET)"; sleep 0.05; \
		printf "\b\b $(CC_BLUE)\\ $(RESET)"; sleep 0.05; \
	done
# Clear the animation and display OK.
	@printf "\b\b $(CC_GREEN)OK!$(RESET)\n"
	$(CC) $(SRC_OBJS) $(LDFLAGS) $(LDLIBS) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) $(DEPFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $@

$(LIBFT):
	@+$(MAKE) -C $(LIBFT_DIR) >/dev/null

$(MLX_LIB):
	@mkdir -p $(MLX_BUILD)
	@cd $(MLX_BUILD) && cmake ..
	@+cmake --build $(MLX_BUILD)

# Cleaning Rules
clean:
	@$(RM) $(OBJ_DIR)
	@+$(MAKE) clean -s -C $(LIBFT_DIR)
	@$(RM) $(MLX_BUILD)
	@echo "$(CC_YELLOW)🕸️  Object files destroyed!$(RESET)"

fclean: clean
	@$(RM) $(BIN_DIR)
	@+$(MAKE) fclean -s -C $(LIBFT_DIR)
	@echo "$(CC_PURPLE)⚰️  Binary buried!$(RESET)"

re: fclean
	@$(MAKE) all --no-print-directory
	@echo "$(CC_GREEN)🦇  The Project has risen from the dead!$(RESET)"

# Include dependency files to track header changes
-include $(DEPS)

# PHONY Targets
.PHONY: all clean fclean re

