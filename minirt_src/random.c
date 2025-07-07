/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:40:40 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:26:31 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/miniRT.h"

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

// Returns a random vector in the unit sphere.
static t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (true)
	{
		p = vec3_create(random_double_range(-1, 1), random_double_range(-1, 1),
				random_double_range(-1, 1));
		if (vec3_length_squared(&p) < 1)
			return (p);
	}
}

t_vec3	random_unit_vector(void)
{
	t_vec3	random_sphere_point;

	random_sphere_point = random_in_unit_sphere();  
		// Store the result in a variable
	return (vec3_unit_vector(&random_sphere_point));
		// Now take the address of the variable
}
