/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2024/07/14 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	is_valid_number(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else if (str[i] == '.' && has_digit)
		{
			if (str[i + 1] == '\0')
				return (0);
			i++;
			while (str[i] && str[i] >= '0' && str[i] <= '9')
				i++;
			break ;
		}
		else
			return (0);
		i++;
	}
	return (has_digit);
}

void	validate_numeric_string(char *str)
{
	if (!str || !*str)
		error_exit("Empty numeric value\n");
	if (!is_valid_number(str))
		error_exit("Invalid numeric format\n");
}

void	validate_color_format(char *color_str)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	if (!color_str || !*color_str)
		error_exit("Empty color value\n");
	colors = ft_split(color_str, ',');
	if (!colors || ft_strarrlen(colors) != 3)
		error_exit("Invalid color format\n");
	validate_numeric_string(colors[0]);
	validate_numeric_string(colors[1]);
	validate_numeric_string(colors[2]);
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Color values out of range [0,255]\n");
	ft_free_split(colors);
}

void	validate_vector_format(char *vector_str)
{
	char	**coords;

	if (!vector_str || !*vector_str)
		error_exit("Empty vector value\n");
	coords = ft_split(vector_str, ',');
	if (!coords || ft_strarrlen(coords) != 3)
		error_exit("Invalid vector format\n");
	validate_numeric_string(coords[0]);
	validate_numeric_string(coords[1]);
	validate_numeric_string(coords[2]);
	ft_free_split(coords);
}

void	validate_normalized_vector(char *vector_str)
{
	char	**coords;
	double	x;
	double	y;
	double	z;
	double	length;

	if (!vector_str || !*vector_str)
		error_exit("Empty vector value\n");
	coords = ft_split(vector_str, ',');
	if (!coords || ft_strarrlen(coords) != 3)
		error_exit("Invalid vector format\n");
	validate_numeric_string(coords[0]);
	validate_numeric_string(coords[1]);
	validate_numeric_string(coords[2]);
	x = ft_atof(coords[0]);
	y = ft_atof(coords[1]);
	z = ft_atof(coords[2]);
	length = x * x + y * y + z * z;
	if (length < 0.0001)
		error_exit("Vector cannot be zero\n");
	if (length < 0.99 || length > 1.01)
		error_exit("Vector must be normalized\n");
	ft_free_split(coords);
}

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