/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:21:23 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/05 23:56:13 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putptr(void *ptr);
int	ft_puthex(int num, char c);
int	ft_putchar(char c);
int	ft_putint(int n);
int	ft_putstr(char *s);
int	ft_putnbru(unsigned int num);
int	ft_putfloat(double n);
#endif