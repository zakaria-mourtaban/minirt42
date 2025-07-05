/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:30:16 by zmourtab          #+#    #+#             */
/*   Updated: 2024/06/29 15:36:53 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_1(int n, int *len)
{
	if (n == -2147483648)
	{
		*len += ft_putchar('-');
		*len += ft_putchar('2');
		n = 147483648;
	}
	if (n < 0)
	{
		*len += ft_putchar('-');
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_1(n / 10, len);
		*len += ft_putchar((n % 10) + '0');
	}
	else
	{
		*len += ft_putchar(n + '0');
	}
}

int	ft_putint(int n)
{
	int	len;

	len = 0;
	ft_putnbr_1(n, &len);
	return (len);
}
