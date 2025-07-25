/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2025/07/20 20:18:24 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	validate_ratio(double ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		error_exit("Ratio must be in range [0.0,1.0]\n");
}

void	validate_fov(double fov)
{
	if (fov <= 0.0 || fov >= 180.0)
		error_exit("FOV must be in range (0.0,180.0)\n");
}

void	validate_positive_double(char *str, char *element_name)
{
	double	value;

	validate_numeric_string(str);
	value = ft_atof(str);
	if (value <= 0.0)
	{
		ft_printf("Error: %s must be positive\n", element_name);
		exit(1);
	}
}
