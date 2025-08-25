/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:20:19 by makarkao          #+#    #+#             */
/*   Updated: 2025/08/25 23:30:42 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**read_map(t_game *game, char *filename)
{
	int		fd;
	char	*line = NULL;
	char	**map;
	char	**sp_line = NULL;
	ssize_t	len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	map = NULL;
	len = 0;
	line = get_next_line(fd, map);
	while (line && !line[0])
	{
		free(line);
		line = get_next_line(fd, map);
	}
	sp_line = ft_split(line, ' ');
	if(!sp_line)
		returtn(printf("Error\n"), NULL);
	if(!sp_line[0] || !sp_line[1] || sp_line[2])
		returtn(printf("Error\n"), NULL);

	
	// close(fd); 
	// return (map);
}
