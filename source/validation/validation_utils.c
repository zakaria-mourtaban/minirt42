/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2025/08/14 00:11:54 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	validate_ratio(double ratio, char **tokens)
{
	if (ratio < 0.0 || ratio > 1.0)
		error_exit("Ratio must be in range [0.0,1.0]\n", tokens);
}

void	validate_fov(double fov, char **tokens)
{
	if (fov <= 0.0 || fov >= 180.0)
		error_exit("FOV must be in range (0.0,180.0)\n", tokens);
}

void	validate_positive_double(char *str, char *element_name, char **tokens)
{
	double	value;

	validate_numeric_string(str, tokens);
	value = ft_atof(str);
	if (value <= 0.0)
	{
		ft_printf("Error: %s must be positive\n", element_name);
		error_exit("element value error \n", tokens);
	}
}
