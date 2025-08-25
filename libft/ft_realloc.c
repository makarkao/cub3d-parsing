/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:02:34 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/26 15:59:55 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc(char **map, char *line, ssize_t k)
{
	ssize_t	i;
	char	**map_r;

	i = 0;
	map_r = malloc(sizeof(char *) * k);
	if (!map_r)
		exit((ft_freemap(map), ft_exitmsg(0), 1));

	while (i < k - 2 && map[i])
	{
		map_r[i] = map[i];
		i++;
	}
	map_r[i++] = line;
	map_r[i] = NULL;
	free(map);
	return (map_r);
}
