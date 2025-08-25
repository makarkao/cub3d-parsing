/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exitmsg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:33:51 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/04 00:01:18 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exitmsg(int n)
{
	if (n == 0)
		ft_printf("ERROR\nMalloc ERROR\n");
	else if (n == 1)
		ft_printf("ERROR\nInvalid MAP\n");
	else if (n == 2)
		ft_printf("ERROR\nfile doesn't exist or Error opening file\n");
	else if (n == 3)
		ft_printf("ERROR\nMlx initialisation Error\n");
	else if (n == 4)
		ft_printf("ERROR\nLoading Image Error\n");
	else if (n == 5)
		ft_printf("ERROR\nInvalid Map Value\n");
	else if (n == 6)
		ft_printf("Game Over\n");
	else if (n == 7)
		ft_printf("Congratulations You Won\n");
	else if (n == 8)
		ft_printf("You exit the game\n");
	else if (n == 9)
		ft_printf("Error\nInvalid Input");
}
