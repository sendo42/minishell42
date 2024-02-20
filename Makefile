CC = gcc
# CFLAGS = -Wall -Wextra -Werror
SRCDIR = .
BUILDDIR = ./builtin
SRCS = $(SRCDIR)/pipex.c $(SRCDIR)/test.c
BUILTIN_SRCS = $(BUILDDIR)/ft_cd.c $(BUILDDIR)/ft_echo.c $(BUILDDIR)/ft_env.c $(BUILDDIR)/ft_export.c $(BUILDDIR)/ft_lib.c $(BUILDDIR)/ft_pwd.c $(BUILDDIR)/ft_unset.c
OBJS = $(SRCS:.c=.o)
BUILTIN_OBJS = $(BUILTIN_SRCS:.c=.o)
TARGET = a.out

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS) $(BUILTIN_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BUILTIN_OBJS)

fclean: clean
	@rm -f $(TARGET)

re: fclean all
