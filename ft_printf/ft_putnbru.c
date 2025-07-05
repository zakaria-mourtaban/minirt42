/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:53:53 by zmourtab          #+#    #+#             */
/*   Updated: 2024/06/29 16:31:15 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbru_1(unsigned int n, int *len)
{
	if (n > 9)
	{
		ft_putnbru_1(n / 10, len);
		*len += ft_putchar((n % 10) + '0');
	}
	else
	{
		*len += ft_putchar(n + '0');
	}
}

int	ft_putnbru(unsigned int num)
{
	int	len;

	len = 0;
	ft_putnbru_1(num, &len);
	return (len);
}
