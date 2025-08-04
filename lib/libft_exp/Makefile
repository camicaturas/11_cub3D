################################################
## ARGUMENTS

NAME = libft_expanded.a
CFLAGS = -Wall -Wextra -Werror
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

# wildcard te lee todos los archivos .c que hay en la carpeta
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

################################################
## RULES

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -r $@ $?
	@echo "$(GREEN)$(NAME) COMPILED!! $(END_COLOR)"
%.o: %.c
	$(CC) -c $(CFLAGS) $?
clean:
	rm -f $(OBJECTS)
	rm -f *.so
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

################################################