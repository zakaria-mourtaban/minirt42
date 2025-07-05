/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:41:10 by zmourtab          #+#    #+#             */
/*   Updated: 2024/06/29 16:19:09 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;

	if (s == NULL)
		return (ft_putstr("(null)"));
	i = 0;
	while (s[i] != '\0')
		i++;
	if (s)
		write (1, s, i);
	return (i);
}
