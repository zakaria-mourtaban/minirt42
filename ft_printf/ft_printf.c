/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:27:59 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/05 23:56:04 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	checkformat(char c, va_list vl)
{
	int	len;

	len = 0;
	if (c == 'd' || c == 'i')
		len += ft_putint(va_arg(vl, int));
	else if (c == 'u')
		len += ft_putnbru(va_arg(vl, int));
	else if (c == 'p')
		len += ft_putptr(va_arg(vl, void *));
	else if (c == 'f')
		len += ft_putfloat(va_arg(vl, double));
	else if (c == 's')
		len += ft_putstr(va_arg(vl, char *));
	else if (c == 'x' || c == 'X')
		len += ft_puthex(va_arg(vl, int), c);
	else if (c == 'c')
		len += ft_putchar(va_arg(vl, int));
	else if (c == '%')
		len += write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			len += checkformat(format[i + 1], args);
			i++;
		}
		else
		{
			len += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (len);
}
// pritnf("dfjbjsdgb v %d ,hgbd %s",64, "jhgd");
// vfldgbjvbfdv 877849488
// int	main(void)
// {
// 	int num = 10;
// 	char *str = "Hello";
// 	char ch = 'A';

// 	int printed_length = ft_printf("Integer: %d, String: %s, Character: %c\n",
// 			num, str, ch);
// 	printf("Length of printed output: %d\n", printed_length);

// 	return (0);
// }