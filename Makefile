SRCS = cub3d.c draw.c move_player.c rays.c sprites.c player_key_hooks.c

OBJS = ${SRCS:.c=.o}

NAME = cub3d

CC = cc
RM = rm -f
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -g
MFLAGS = -L ./mlx_linux -lmlx -lXext -lX11 -lm
CMAKE = make -C

LIBFTDIR = libft/

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CMAKE} mlx_linux/
	${CC} ${CFLAGS} ${OBJS} ${MFLAGS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re