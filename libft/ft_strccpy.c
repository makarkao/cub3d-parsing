/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 21:02:37 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/01 21:07:28 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strccpy(char *str)
{
	size_t	j;
	size_t	k;
	char	*str_c;

	j = ft_strlennl(str);
	str_c = malloc(sizeof(char) * (j + 1));
	if (!str_c)
		return (NULL);
	k = 0;
	while (k < j)
	{
		str_c[k] = str[k];
		k++;
	}
	str_c[k] = '\0';
	return (str_c);
}
