/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:21:28 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/20 20:27:02 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	validate_plane(char **tokens, int count)
{
	if (count != 4)
		error_exit("Plane: wrong number of arguments (expected 4)\n");
	validate_vector_format(tokens[1]);
	validate_normalized_vector(tokens[2]);
	validate_color_format(tokens[3]);
}

void	validate_sphere(char **tokens, int count)
{
	if (count != 4)
		error_exit("Sphere: wrong number of arguments (expected 4)\n");
	validate_vector_format(tokens[1]);
	validate_positive_double(tokens[2], "Sphere diameter");
	validate_color_format(tokens[3]);
}

void	validate_cylinder(char **tokens, int count)
{
	if (count != 6)
		error_exit("Cylinder: wrong number of arguments (expected 6)\n");
	validate_vector_format(tokens[1]);
	validate_normalized_vector(tokens[2]);
	validate_positive_double(tokens[3], "Cylinder diameter");
	validate_positive_double(tokens[4], "Cylinder height");
	validate_color_format(tokens[5]);
}
