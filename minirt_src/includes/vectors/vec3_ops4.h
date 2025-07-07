/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops4.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:39:55 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:48:11 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS4_H
# define VEC3_OPS4_H

# include "vec3_defs.h"

// Forward declarations to resolve implicit declaration errors
double					random_double(void);
double					random_double_range(double min, double max);

static inline t_vec3	vec3_random(void)
{
	return (vec3_create(random_double(), random_double(), random_double()));
}

static inline t_vec3	vec3_random_range(double min, double max)
{
	return (vec3_create(random_double_range(min, max), random_double_range(min,
				max), random_double_range(min, max)));
}

static inline t_vec3	random_unit_vector(void)
{
	t_vec3	p;
	double	lensq;

	while (1)
	{
		p = vec3_random_range(-1, 1);
		lensq = vec3_length_squared(&p);
		if (1e-160 < lensq && lensq <= 1)
			return (vec3_divide(&p, sqrt(lensq)));
	}
}

static inline t_vec3	random_on_hemisphere(const t_vec3 *normal)
{
	t_vec3	on_unit_sphere;

	on_unit_sphere = random_unit_vector();
	if (vec3_dot(&on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	else
		return (vec3_negate(&on_unit_sphere));
}

#endif