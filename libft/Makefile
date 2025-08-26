SRCS = ft_strcmp.c free_strs.c get_next_line.c get_next_line_utils.c ft_split.c ft_strlennl.c ft_strslen.c ft_strccpy.c ft_strscpy.c ft_itoa.c ft_freemap.c ft_freestrs.c ft_realloc.c ft_printf.c ft_printf_funcs.c ft_exitmsg.c
OBJS = ${SRCS:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS} 

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
