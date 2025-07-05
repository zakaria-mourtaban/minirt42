/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:50:53 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/05 23:55:58 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putlong(long n, int *len)
{
	if (n == -9223372036854775807L - 1L)
	{
		*len += ft_putchar('-');
		*len += ft_putchar('9');
		ft_putlong(223372036854775807L, len);
		*len += ft_putchar('8');
		return ;
	}
	if (n < 0)
	{
		*len += ft_putchar('-');
		n *= -1;
	}
	if (n > 9)
		ft_putlong(n / 10, len);
	*len += ft_putchar((n % 10) + '0');
}

static void	ft_putfrac(long n, int *len)
{
	long	temp;
	int		digits;
	int		i;
	int		precision;

	precision = 6;
	temp = n;
	digits = 0;
	if (temp == 0)
		digits = 1;
	while (temp > 0)
	{
		temp /= 10;
		digits++;
	}
	i = 0;
	while (i++ < precision - digits)
		*len += ft_putchar('0');
	ft_putlong(n, len);
}

int	ft_putfloat(double n)
{
	int		len;
	long	ipart;
	double	fpart;
	long	decimals;

	len = 0;
	if (n < 0 || (n == 0.0 && 1.0 / n < 0))
	{
		len += ft_putchar('-');
		n *= -1;
	}
	ipart = (long)n;
	fpart = n - (double)ipart;
	decimals = (long)(fpart * 1000000.0 + 0.5);
	if (decimals >= 1000000)
	{
		ipart++;
		decimals = 0;
	}
	ft_putlong(ipart, &len);
	len += ft_putchar('.');
	ft_putfrac(decimals, &len);
	return (len);
}
