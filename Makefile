CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar rcs
NAME = push_swap
HEADERS := -I ./include

SRCS := $(shell find ./src -iname "*.c")
OBJS := ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

allc: all clean

clean:
	rm -f $(OBJS)
	rm -f *.so

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re allc
