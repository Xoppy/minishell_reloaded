# Name of the final static library
NAME = libftprintf.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# BEGIN SRC
SRC = \
    ft_printf.c \
    ft_printf_X.c \
    ft_printf_char.c \
    ft_printf_d.c \
    ft_printf_p.c \
    ft_printf_parser.c \
    ft_printf_s.c \
    ft_printf_u.c \
    ft_printf_x.c \
    ft_puthexl_fd.c \
    ft_puthexu_fd.c \
    ft_putptr_fd.c
# END SRC (line number: 14)

# Object files generated from ft_printf source files
FT_PRINTF_OBJS = $(SRC:.c=.o)

# Directory for libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Include directory for ft_printf and libft
INCLUDES = -I ./ -I $(LIBFT_DIR)

# Default rule to build everything (static library)
all: $(NAME)

# Build the final static library
$(NAME): $(FT_PRINTF_OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)           # Copy libft.a to libftprintf.a
	ar rcs $(NAME) $(FT_PRINTF_OBJS) # Add ft_printf object files to libftprintf.a

# Build the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to compile ft_printf object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files
clean:
	rm -f $(FT_PRINTF_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean everything, including the final static library
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
