CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AR = ar rcs
NAME = push_swap
LIBFT = libft
HEADERS := -I ./include

SRCS := $(shell find ./src -iname "*.c")
OBJS := ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(HEADERS) libft/libft.a -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

allc: all clean
	@echo "Making all and cleaning up"

clean:
	make clean -C $(LIBFT)
	${RM} $(OBJS)
	@echo "Removing everything but library and source files"

fclean: clean
	make fclean -C $(LIBFT)
	${RM} ${NAME} libft.a

re: fclean all clean
	@echo "Cleaning up and redoing all"

lib:
	make -C $(LIBFT)
	@echo "Recreating libft library"

.PHONY: all clean fclean re allc lib
