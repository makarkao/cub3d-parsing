/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:10:12 by makarkao          #+#    #+#             */
/*   Updated: 2025/08/25 13:47:21 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdarg.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# elif BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct sp_var
{
	size_t			i;
	size_t			j;
	size_t			k;
}					t_spvar;

typedef struct s_gnlsv
{
	ssize_t	k;
	char	*s;
}			t_gnlsv;

typedef struct s_gnlnsv
{
	ssize_t	j;
	ssize_t	i;
	char	*l;
}			t_gnlnsv;

int			ft_printf(const char *str, ...);
int			ft_putchar(char c);
int			ft_putstr(char *s);
int			ft_putnbr(int n);
char		*get_next_line(int fd, char **map);
char		*ft_get_nxt_line_prc(t_gnlsv *v, t_gnlnsv *x, int fd, char **map);
char		*ft_strcpy(char *str, char *s);
size_t		ft_strlen(char *str);
size_t		ft_strchr(char *str, ssize_t *j, char c);
char		*ft_sub(char *str, char *s, ssize_t *k, size_t size2);
size_t		ft_strlennl(char *str);
size_t		ft_strslen(char **strs);
char		*ft_strccpy(char *str);
char		**ft_strscpy(char **map);
char		*ft_itoa(int x);
void		ft_freestrs(char **str, size_t k);
void		ft_freemap(char **map);
char		**ft_realloc(char **map, char *line, ssize_t k);
void		ft_exitmsg(int n);
char		**ft_split(char *s, char c);

#endif