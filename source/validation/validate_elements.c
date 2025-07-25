/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:21:18 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/20 20:25:05 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	validate_ambient(char **tokens, int count, int *a_flag)
{
	double	ratio;

	if (count != 3)
		error_exit("Ambient: wrong number of arguments (expected 3)\n");
	if (*a_flag)
		error_exit("Error: only ambient lights one allowed \n");
	*a_flag = 1;
	validate_numeric_string(tokens[1]);
	ratio = ft_atof(tokens[1]);
	validate_ratio(ratio);
	validate_color_format(tokens[2]);
}

void	validate_camera(char **tokens, int count, int *c_flag)
{
	double	fov;

	if (count != 4)
		error_exit("Camera: wrong number of arguments (expected 4)\n");
	if (*c_flag)
		error_exit("Error: Multiple cameras defined (only one allowed)\n");
	*c_flag = 1;
	validate_vector_format(tokens[1]);
	validate_normalized_vector(tokens[2]);
	validate_numeric_string(tokens[3]);
	fov = ft_atof(tokens[3]);
	validate_fov(fov);
}

void	validate_light(char **tokens, int count, int *l_flag)
{
	double	brightness;

	if (count != 3)
		error_exit("Light: wrong number of arguments (expected 3)\n");
	if (*l_flag)
		error_exit("Error: Multiple lights defined (only one allowed)\n");
	*l_flag = 1;
	validate_vector_format(tokens[1]);
	validate_numeric_string(tokens[2]);
	brightness = ft_atof(tokens[2]);
	validate_ratio(brightness);
}
