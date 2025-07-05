/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:48:55 by zmourtab          #+#    #+#             */
/*   Updated: 2024/06/29 16:30:36 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrhexp(unsigned long long nb, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnbrhexp((nb / 16), len);
		ft_putnbrhexp((nb % 16), len);
	}
	else
		*len += ft_putchar(hexa[nb]);
}

int	ft_putptr(void *ptr)
{
	unsigned long long	num;
	int					len;

	len = 0;
	num = (unsigned long long)ptr;
	if (num == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putchar('0');
	ft_putchar('x');
	ft_putnbrhexp(num, &len);
	return (len + 2);
}
