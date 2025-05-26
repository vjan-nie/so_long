# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 12:24:16 by vjan-nie          #+#    #+#              #
#    Updated: 2025/05/26 10:20:49 by vjan-nie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	so_long

# Paths

SRC_DIR = src

INCLUDE_DIR = includes

LIBFT_DIR = libft

MINILIBX_DIR = minilibx-linux

OBJ_DIR = obj

# Libft

LIBFT	=	$(LIBFT_DIR)/libft.a

LIBFT_INCLUDE	= -I$(LIBFT_DIR)/include

# Minilibx

MINILIBX	=	$(MINILIBX_DIR)/libmlx_linux.a

# Source files

SRC		=	$(SRC_DIR)/main.c\
			$(SRC_DIR)/so_long.c\
			$(SRC_DIR)/so_long_utils.c\
			$(SRC_DIR)/arg_check.c\
			$(SRC_DIR)/errors.c\
			$(SRC_DIR)/map_utils_1.c\
			$(SRC_DIR)/map_utils_2.c

# Objects

OBJ		= 	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiling rules

CC		= 	cc

CFLAGS	= 	-Wall -Wextra -Werror

MINILIBX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

# Includes

INCLUDES = -I$(INCLUDE_DIR) $(LIBFT_INCLUDE) $(MINILIBX_INCLUDE)

MINILIBX_INCLUDE	= -I$(MINILIBX_DIR)
# Building commands:

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(MINILIBX_INCLUDE) $(OBJ) $(LIBFT) $(MINILIBX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR) || true

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(MINILIBX_INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	-@$(MAKE) -C $(MINILIBX_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
