/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:02:26 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/01 21:05:34 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freestrs(char **strs, size_t k)
{
	size_t	i;

	i = 0;
	if (!strs)
		return ;
	while (i < k)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
