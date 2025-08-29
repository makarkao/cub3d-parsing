SRCS = cub3d.c ./parsing/parsing.c ./parsing/read_map.c ./parsing/fill_map.c ./parsing/read_cube_file.c
# SRCS = cub3d.c draw.c move_player.c rays.c sprites.c player_key_hooks.c

OBJS = ${SRCS:.c=.o}

NAME = cub3d

CC = cc
RM = rm -f
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS =  -g
MFLAGS = -L ./mlx_linux -lmlx -lXext -lX11 -lm
# MFLAGS = 
CMAKE = make -C

# LIBFTDIR = libft/

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -I./libft -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	# ${CMAKE} mlx_linux/
	${CC} ${CFLAGS} ${OBJS} ${MFLAGS} -o ${NAME} -L ./libft -lft

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re