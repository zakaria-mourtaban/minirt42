/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:43:25 by zmourtab          #+#    #+#             */
/*   Updated: 2024/06/29 16:28:51 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrhexa(unsigned int nb, char c, int *len)
{
	char	*hexa;

	if (c == 'X')
		hexa = "0123456789ABCDEF";
	else if (c == 'x')
		hexa = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnbrhexa((nb / 16), c, len);
		ft_putnbrhexa((nb % 16), c, len);
	}
	else
		*len += ft_putchar(hexa[nb]);
}

int	ft_puthex(int num, char c)
{
	int	len;

	len = 0;
	ft_putnbrhexa(num, c, &len);
	return (len);
}
