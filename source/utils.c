/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2024/07/14 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

double	ft_atof(const char *str)
{
	double	res;
	double	frac;
	double	sign;
	int		dot;
	int		i;

	res = 0.0;
	frac = 0.1;
	sign = 1.0;
	dot = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
	{
		if (str[i] == '.')
		{
			dot = 1;
			i++;
			continue ;
		}
		if (!dot)
			res = res * 10.0 + (str[i] - '0');
		else
		{
			res = res + (str[i] - '0') * frac;
			frac *= 0.1;
		}
		i++;
	}
	return (res * sign);
}

int	ft_strarrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error_exit(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	exit(1);
}