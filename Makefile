NAME = bsq
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/map_parser.c \
       $(SRCS_DIR)/solver.c \
       $(SRCS_DIR)/utils.c \
       $(SRCS_DIR)/extra_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
