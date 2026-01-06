# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/31 09:06:36 by joaolive          #+#    #+#              #
#    Updated: 2025/11/10 15:46:12 by joaolive         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final library
NAME = libft.a

# Colors
CC_PINK = \033[38;2;255;121;198m
CC_BLUE = \033[38;2;139;233;253m
CC_YELLOW = \033[38;2;241;250;140m
RESET = \033[0m

# Tools
CC = cc
AR = ar rcs
RM = rm -rf

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Flags and Includes
CCFLAGS = -Wall -Wextra -Werror
DEPFLAGS = -MMD -MP
CPPFLAGS = -Iinclude -Isrc/core -Isrc/lst -Isrc/dlst -Isrc/gnl -Isrc/printf

CORE_NAMES = $(addsuffix .c, \
			ft_isalpha \
			ft_isdigit \
			ft_isalnum \
			ft_isascii \
			ft_isprint \
			ft_isspace \
			ft_is_numeric \
			ft_strlen \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_strlcpy \
			ft_strlcat \
			ft_toupper \
			ft_tolower \
			ft_strchr \
			ft_strrchr \
			ft_strncmp \
			ft_memchr \
			ft_memcmp \
			ft_strnstr \
			ft_atoi \
			ft_calloc \
			ft_realloc \
			ft_strdup \
			ft_substr \
			ft_strjoin \
			ft_strjoinv \
			ft_strtrim \
			ft_split \
			ft_itoa \
			ft_strmapi \
			ft_striteri \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putunbr_fd \
			ft_atol \
			ft_strcmp \
			ft_strdup_matrix)

LST_NAMES = $(addsuffix .c, \
			ft_lstnew \
			ft_lstadd_front \
			ft_lstsize \
			ft_lstlast \
			ft_lstadd_back \
			ft_lstdelone \
			ft_lstclear \
			ft_lstiter \
			ft_lstmap)

DLST_NAMES = $(addsuffix .c, \
			ft_dlstdestroy \
			ft_dlstdetach_node \
			ft_dlstclear \
			ft_dlstdelone \
			ft_dlstfind \
			ft_dlstforeach_ctx \
			ft_dlstforeach \
			ft_dlstget_node_at \
			ft_dlstinit \
			ft_dlstinsert_at \
			ft_dlstinsert_node_at \
			ft_dlstiter \
			ft_dlstmap \
			ft_dlstnew \
			ft_dlstpeek_at \
			ft_dlstpeek_back \
			ft_dlstpeek_front \
			ft_dlstpop_back \
			ft_dlstpop_front \
			ft_dlstpush_back \
			ft_dlstpush_front \
			ft_dlstpush_node_back \
			ft_dlstpush_node_front \
			ft_dlstremove_at \
			ft_dlstremove_if \
			ft_dlstremove_node \
			ft_dlstreverse \
			ft_dlstconcat \
			ft_dlstget_node_index)

GNL_NAMES = $(addsuffix .c, get_next_line)

PRINTF_NAMES = $(addsuffix .c, \
			ft_printf \
			ft_handler_format \
			ft_print_char \
			ft_print_num \
			ft_print_str \
			ft_print_unum \
			ft_print_lhex \
			ft_print_chex \
			ft_print_ptr \
			ft_print_percent \
			ft_puthex)

# Source files
CORE_SRCS = $(addprefix $(SRC_DIR)/core/, $(CORE_NAMES))
LST_SRCS = $(addprefix $(SRC_DIR)/lst/, $(LST_NAMES))
DLST_SRCS = $(addprefix $(SRC_DIR)/dlst/, $(DLST_NAMES))
GNL_SRCS = $(addprefix $(SRC_DIR)/gnl/, $(GNL_NAMES))
PRINTF_SRCS = $(addprefix $(SRC_DIR)/printf/, $(PRINTF_NAMES))

# Object files
CORE_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CORE_SRCS))
LST_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LST_SRCS))
DLST_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(DLST_SRCS))
GNL_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(GNL_SRCS))
PRINTF_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PRINTF_SRCS))

# Dependencies
ALL_OBJS = $(CORE_OBJS) $(LST_OBJS) $(DLST_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
DEPS = $(ALL_OBJS:.o=.d)

all:
		@echo "                                    "
		@echo "██╗░░░░░██╗██████╗░███████╗████████╗"
		@echo "██║░░░░░██║██╔══██╗██╔════╝╚══██╔══╝"
		@echo "██║░░░░░██║██████╦╝█████╗░░░░░██║░░░"
		@echo "██║░░░░░██║██╔══██╗██╔══╝░░░░░██║░░░"
		@echo "███████╗██║██████╦╝██║░░░░░░░░██║░░░"
		@echo "╚══════╝╚═╝╚═════╝░╚═╝░░░░░░░░╚═╝░░░"
		@echo "                                    "
		@$(MAKE) build

build: $(NAME)
	@echo ""
	@echo "───────────────────────────────────────────────"
	@echo " 🎯 Libft is up to date! Nothing to rebuild 🚀"
	@echo "───────────────────────────────────────────────"
	@echo ""

# default rule: compile ALL modules
$(NAME): $(ALL_OBJS)
	@$(AR) $@ $^
	@echo "🎉 $(NAME) compiled successfully with ALL modules 🚀"

# Include dependency files to track header changes
-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "  $(CC_BLUE)[CC]$(RESET) Compiling $(CC_YELLOW)%s$(RESET) -> $(CC_PINK)%s$(RESET)\n" $< $@
	@$(CC) $(CCFLAGS) $(DEPFLAGS) $(CPPFLAGS) -c $< -o $@

# Cleaning Rules
clean:
	@$(RM) $(OBJ_DIR)
	@echo "🧼 Object files cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@echo "🧹 Full clean complete! Library removed."

re: fclean all
	@echo "🚀 Project has been rebuilt from scratch!"

# PHONY Targets
.PHONY: all clean fclean re
