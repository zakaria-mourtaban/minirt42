/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:21:18 by mkraytem          #+#    #+#             */
/*   Updated: 2025/08/14 00:13:03 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	validate_ambient(char **tokens, int count, int *a_flag)
{
	double	ratio;

	if (count != 3)
		error_exit("Ambient: wrong number of arguments (expected 3)\n", tokens);
	if (*a_flag)
		error_exit("Error: only ambient lights one allowed \n", tokens);
	*a_flag = 1;
	validate_numeric_string(tokens[1], tokens);
	ratio = ft_atof(tokens[1]);
	validate_ratio(ratio, tokens);
	validate_color_format(tokens[2], tokens);
}

void	validate_camera(char **tokens, int count, int *c_flag)
{
	double	fov;

	if (count != 4)
		error_exit("Camera: wrong number of arguments (expected 4)\n", tokens);
	if (*c_flag)
		error_exit("Error: only one camera allowed\n", tokens);
	*c_flag = 1;
	validate_vector_format(tokens[1], tokens);
	validate_normalized_vector(tokens[2], tokens);
	validate_numeric_string(tokens[3], tokens);
	fov = ft_atof(tokens[3]);
	validate_fov(fov, tokens);
}

void	validate_light(char **tokens, int count, int *l_flag)
{
	double	brightness;

	if (count != 3)
		error_exit("Light: expected 3 arguments\n", tokens);
	if (*l_flag)
		error_exit("Error: only one light allowed\n", tokens);
	*l_flag = 1;
	validate_vector_format(tokens[1], tokens);
	validate_numeric_string(tokens[2], tokens);
	brightness = ft_atof(tokens[2]);
	validate_ratio(brightness, tokens);
}
