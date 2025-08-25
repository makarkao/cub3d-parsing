/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:39:11 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/03 17:39:13 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

static int	ft_putnbr_pstv(long n)
{
	int	i;

	i = 0;
	if (n < 0)
		(1) && (i++, n = -n);
	if (n >= 10)
		i += ft_putnbr_pstv(n / 10);
	return (i += ft_putchar((n % 10) + '0'));
}

int	ft_putnbr(int n)
{
	long	x;

	x = (long)n;
	if (x < 0)
		ft_putchar('-');
	return (ft_putnbr_pstv(x));
}
