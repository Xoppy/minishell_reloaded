# Variables
NAME = test_gnl
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

# Default target to build the executable
all: $(NAME)

# Link objects to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile each .c file into a .o file
%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	$(RM) $(OBJS)

# Clean up object files and the executable
fclean: clean
	$(RM) $(NAME)

# Rebuild the project
re: fclean all
