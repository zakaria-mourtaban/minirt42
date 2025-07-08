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

#include "includes/random.h"
#include "includes/vectors/vec3.h"
#include <stdlib.h>

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

static t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	p = vec3_create(random_double_range(-1, 1), random_double_range(-1, 1),
			random_double_range(-1, 1));
	while (vec3_length_squared(&p) >= 1)
	{
		p = vec3_create(random_double_range(-1, 1), random_double_range(-1, 1),
				random_double_range(-1, 1));
	}
	return (p);
}

t_vec3	random_unit_vector(void)
{
	t_vec3	random_sphere_point;

	random_sphere_point = random_in_unit_sphere();
	return (vec3_unit_vector(&random_sphere_point));
}

t_vec3	random_on_hemisphere(const t_vec3 *normal)
{
	t_vec3	random_vec;

	random_vec = random_unit_vector();
	if (vec3_dot(&random_vec, normal) > 0.0)
		return (random_vec);
	else
		return (vec3_negate(&random_vec));
}
