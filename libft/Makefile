NAME = libft.a                  # Static library name
CC = gcc                        # Compiler
CFLAGS = -Wall -Wextra -Werror  # Compiler flags
SRC = ft_atoi.c \
    ft_atol.c \
    ft_bzero.c \
    ft_calloc.c \
    ft_count_digits.c \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_memset.c \
    ft_strchr.c \
    ft_strdup.c \
    ft_strlcat.c \
    ft_strlcpy.c \
    ft_strlen.c \
    ft_strcmp.c \
    ft_strncmp.c \
    ft_strnstr.c \
    ft_strrchr.c \
    ft_tolower.c \
    ft_toupper.c \
    ft_substr.c \
    ft_strjoin.c \
    ft_strtrim.c \
    ft_split.c \
    ft_itoa.c \
    ft_strmapi.c \
    ft_striteri.c \
    ft_putchar_fd.c \
    ft_putstr_fd.c \
    ft_putendl_fd.c \
    ft_putnbr_fd.c \
    get_next_line.c \
    get_next_line_utils.c         # Source files
OBJ = $(SRC:.c=.o)              # Corresponding object files derived from .c files

# Rule to build the static library
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Default target
all: $(NAME)

# Rule to build object files
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJ)

# Clean up all build files (object files and libraries)
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
