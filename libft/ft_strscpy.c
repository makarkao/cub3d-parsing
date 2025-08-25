/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:02:43 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/03 23:49:27 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strscpy(char **map)
{
	size_t	j;
	size_t	k;
	char	**map_c;

	j = ft_strslen(map);
	map_c = malloc(sizeof(char *) * (j + 1));
	if (!map_c)
		exit((ft_freemap(map), ft_exitmsg(0), 1));
	k = 0;
	while (map[k])
	{
		map_c[k] = ft_strccpy(map[k]);
		if (!map_c[k])
			exit((ft_freemap(map), ft_freestrs(map_c, k), ft_exitmsg(0),
					1));
		k++;
	}
	map_c[k] = NULL;
	return (map_c);
}
