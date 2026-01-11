# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/06 05:55:59 by joaolive          #+#    #+#              #
#    Updated: 2026/01/09 17:54:20 by joaolive         ###   ########.fr        #
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
SRC_CORE = init_graphics
SRC_RENDER = render_bg

# Source files
SRC = \
	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_MAIN))) \
	$(addprefix $(SRC_DIR)/core/, $(addsuffix .c, $(SRC_CORE))) \
	$(addprefix $(SRC_DIR)/render/, $(addsuffix .c, $(SRC_RENDER)))

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
	@cd $(MLX_BUILD) && cmake .. >/dev/null 2>&1
	@+cmake --build $(MLX_BUILD) >/dev/null 2>&1

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

