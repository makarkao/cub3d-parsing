/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:38:36 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/03 23:49:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_nxt_line_prc(t_gnlsv *v, t_gnlnsv *x, int fd, char **map)
{
	while (v->s[0] != 0)
	{
		x->j += ft_strchr(v->s, &(v->k), '\n');
		x->l = ft_sub(x->l, v->s, &(v->k), (x->j - v->k));
		if (!x->l)
			exit((free(v->s), ft_freemap(map), ft_exitmsg(0), 1));
		if (v->s[v->k] == '\n')
		{
			(v->k)++;
			break ;
		}
		if (v->s[v->k] == '\0')
		{
			x->i = read(fd, v->s, BUFFER_SIZE);
			if (x->i == -1)
				return (free(x->l), NULL);
			(1) && (v->s[x->i] = '\0', v->k = 0);
		}
	}
	if (v->s[0] == 0)
	{
		free(v->s);
		v->s = NULL;
	}
	return (x->l);
}

char	*get_next_line(int fd, char **map)
{
	static t_gnlsv	v;
	t_gnlnsv		x;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	(1) && (x.j = 0, x.l = NULL);
	if (v.s == NULL || v.s[v.k] == 0)
	{
		if (!v.s)
		{
			v.s = malloc(sizeof(char) * (((size_t)BUFFER_SIZE) + 1));
			if (!v.s)
				exit((ft_freemap(map), ft_exitmsg(0), 1));
		}
		x.i = read(fd, v.s, BUFFER_SIZE);
		if (x.i == -1)
			return (free(v.s), v.s = NULL, NULL);
		(1) && (v.s[x.i] = '\0', v.k = 0);
	}
	return (ft_get_nxt_line_prc(&v, &x, fd, map));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	//char	buffer[1024];
// 	//int		i;
// 	fd = open("ggggg.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		exit(EXIT_FAILURE);
// 	}
// 	//i = 0;
// 	line = get_next_line(fd);
// 	char *line2 = get_next_line(fd);
// 	ft_printf("%s", line2);
// 	free(line2);
// 	close(fd);
// 	ft_printf("%s", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
