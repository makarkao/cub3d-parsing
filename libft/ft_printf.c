/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:38:53 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/03 17:38:56 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counter_case(va_list args, char c)
{
	int	i;

	i = 0;
	if (c == 'c')
		i = ft_putchar(va_arg(args, int));
	else if (c == 's')
		i = ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		i = ft_putnbr(va_arg(args, int));
	else if (c == '%')
		i = ft_putchar('%');
	else
		i = ft_putchar('%') + ft_putchar(c);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		k;

	(1) && (va_start(args, str), i = 0, k = 0);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			return (-1);
		else if (str[i] == '%' && str[i + 1])
			(1) && (k += counter_case(args, str[i + 1]), i++);
		else
			k += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (k);
}

// int main()
// {
//     char const *str = "jfh%ddhjf%dh %s mm%c %c %c %c %c";
//     int k = ft_ft_printf(str,2,3,"fhfh",'f', 'a', 'b', 's', 'e');
//     ft_printf("\n%d\n",k);
//     return (0);
// }
