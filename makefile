# DELETE -G AT CFLAGS TO DISABLE DEBUGGING
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I/opt/homebrew/opt/readline/include
#part with -L/opt/homebrew/opt/readline/include for macOs
SRCDIR = src
OBJDIR = OBJ
SRCS = $(shell find $(SRCDIR) -type f -name '*.c')
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
LIBS = -L/opt/homebrew/opt/readline/lib -lreadline
# part with -L/opt/homebrew/opt/readline/lib for macOs


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all \
	--suppressions=./supps/	readline.supp ./$(NAME)
