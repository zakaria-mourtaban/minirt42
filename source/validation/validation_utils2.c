/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:17:06 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/25 13:47:59 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_valid_number(char *str)
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
	if (x < -1.0 || x > 1.0
		|| y < -1.0 || y > 1.0
		|| z < -1.0 || z > 1.0)
	{
		ft_free_split(coords);
		error_exit("Vector components must be in range [-1, 1]\n");
	}
	ft_free_split(coords);
}
