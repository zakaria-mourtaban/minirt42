/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:21:28 by mkraytem          #+#    #+#             */
/*   Updated: 2025/08/14 00:11:06 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	validate_plane(char **tokens, int count)
{
	if (count != 4)
		error_exit("Plane: expected arguments  4\n", tokens);
	validate_vector_format(tokens[1], tokens);
	validate_normalized_vector(tokens[2], tokens);
	validate_color_format(tokens[3], tokens);
}

void	validate_sphere(char **tokens, int count)
{
	if (count != 4)
		error_exit("Sphere: expected 4 arguments\n", tokens);
	validate_vector_format(tokens[1], tokens);
	validate_positive_double(tokens[2], "Sphere diameter", tokens);
	validate_color_format(tokens[3], tokens);
}

void	validate_cylinder(char **tokens, int count)
{
	if (count != 6)
		error_exit("Cylinder: expected 6 arguments\n", tokens);
	validate_vector_format(tokens[1], tokens);
	validate_normalized_vector(tokens[2], tokens);
	validate_positive_double(tokens[3], "Cylinder diameter", tokens);
	validate_positive_double(tokens[4], "Cylinder height", tokens);
	validate_color_format(tokens[5], tokens);
}
