# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 14:55:32 by ohosnedl          #+#    #+#              #
#    Updated: 2025/06/03 11:36:13 by cberneri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################
## ARGUMENTS

NAME	= cube3d
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBFT	= ./lib/libft_exp
LIBMLX	= ./lib/MLX42
CC = cc

################################################
## COLORS

# Reset
END_COLOR	= \033[0m       # Text Reset

# Regular Colors
BLACK	= \033[0;30m        # Black
RED		= \033[0;31m          # Red
GREEN	= \033[0;32m        # Green
YELLOW	= \033[0;33m       # Yellow
BLUE	= \033[0;34m         # Blue
PURPLE	= \033[0;35m       # Purple
CYAN	= \033[0;36m         # Cyan
WHITE	= \033[0;37m        # White

################################################
## SOURCES

HEADERS := -I ./sources/cube3d.h -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L$(LIBFT) -lft_expanded
SOURCES = \
	sources/controllers/draw_controller.c \
	sources/controllers/error_controller.c \
	sources/controllers/items_controller.c \
	sources/controllers/loop_controller.c \
	sources/controllers/raycast_controller.c \
	sources/controllers/textures_controller.c \
	sources/controllers/window_controller.c \
	sources/init/initialization.c \
	sources/init/parsing.c \
	sources/init/player_parsing.c \
	sources/utils/raycast_utils.c \
	sources/utils/map_utils.c \
	sources/utils/maps_check_utils.c \
	sources/utils/minimap_utils.c \
	sources/utils/debug_tools.c \
	sources/utils/draw_utils.c \
	sources/utils/keyboard.c \
	sources/utils/texture_utils.c \
	sources/utils/player_utils.c \
	sources/views/draw_minimap_view.c \
	sources/views/draw_textures_view.c \
	sources/main.c

#sources/controllers/map_controller.c \

OBJECTS	:= ${SOURCES:.c=.o}

################################################
## RULES

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(NAME) COMPILED!! $(END_COLOR)"

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
