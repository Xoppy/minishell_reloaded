# ================================
#          Project Makefile
# ================================

# Target executable
NAME       := minishell

# Compiler & flags
CC         := gcc
CFLAGS     := -Wall -Wextra -Werror -g

# Directories
SRCDIR     := .
UTILSDIR   := ./utils
BUILTINS   := ./utils/builtins
LIBFTDIR   := ./libft
PRINTFDIR  := $(LIBFTDIR)/ft_printf

# Include paths
INCLUDES   := \
	-I$(UTILSDIR) \
	-I$(LIBFTDIR) \
	-I$(PRINTFDIR)

# Source files
SRCS       := \
	src/main.c \
	src/init_env.c \
	src/prompt.c \
	src/tokenizer.c \
	src/parser/parser.c \
	src/parser/parser_utils.c \
	src/executor/executor.c \
	src/executor/pipe.c \
	src/executor/redirect.c \
	src/builtins/cd.c \
	src/builtins/cd_utils.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/export.c \
	src/builtins/export_utils.c \
	src/builtins/unset.c \
	src/builtins/pwd.c \
	src/builtins/exit.c \
	src/utils/memory.c \
	src/utils/errors.c \
	src/utils/str_utils.c \
	src/utils/ft_strdup_arr.c \
	src/utils/ft_strj_arr.c \
	src/utils/env_utils.c \
	src/utils/heredoc_utils.c \
	src/utils/path_utils.c \
	src/utils/expansions.c \
	src/utils/expansions_utils.c \
	src/signals.c

# Object files
OBJS       := $(SRCS:.c=.o)

# Static libraries
LIBFT      := $(LIBFTDIR)/libft.a
PRINTFLIB  := $(PRINTFDIR)/libftprintf.a

# Linker flags: readline & ncurses
LDLIBS     := -lreadline -lncurses

.PHONY: all clean fclean re

all: $(LIBFT) $(PRINTFLIB) $(NAME)

# Build the final executable
$(NAME): $(OBJS)
	@echo "Linking $(NAME)…"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTFLIB) $(LDLIBS) -o $@

# Build libft
$(LIBFT):
	@echo "Building libft…"
	$(MAKE) -C $(LIBFTDIR)

# Build ft_printf
$(PRINTFLIB):
	@echo "Building ft_printf…"
	$(MAKE) -C $(PRINTFDIR)

# Compile each .c → .o
%.o: %.c
	@echo "Compiling $<…"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files…"
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(PRINTFDIR) clean

fclean: clean
	@echo "Removing binaries and libraries…"
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(PRINTFLIB)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(PRINTFDIR) fclean

re: fclean all
	@echo "Rebuilt everything."
