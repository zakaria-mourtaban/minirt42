/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:10:53 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 12:12:21 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/vectors/vec3.h"
#include "includes/random.h"

// Lambertian scatter logic
bool	lambertian_scatter(const t_material *self, const t_ray *r_in,
		const struct s_hit_record *rec, t_color *attenuation,
		t_ray *scattered)
{
	t_vec3	scatter_direction;
	t_vec3	rand_unit;

	(void)r_in;
	rand_unit = random_unit_vector();
	scatter_direction = vec3_add(&rec->normal, &rand_unit);
	if (vec3_near_zero(&scatter_direction))
	{
		scatter_direction = rec->normal;
	}
	*scattered = ray_create(rec->p, scatter_direction);
	*attenuation = self->albedo;
	return (true);
}

bool	metal_scatter(const t_material *self, const t_ray *r_in,
		const struct s_hit_record *rec, t_color *attenuation,
		t_ray *scattered)
{
	t_vec3	reflected;
	t_vec3	fuzzed_reflected;
	t_vec3	rand_unit;

	reflected = vec3_reflect(&r_in->dir, &rec->normal);
	rand_unit = random_unit_vector();
	vec3_scale_inplace(&rand_unit, self->fuzz);
	fuzzed_reflected = vec3_add(&reflected, &rand_unit);
	*scattered = ray_create(rec->p, fuzzed_reflected);
	*attenuation = self->albedo;
	return (vec3_dot(&scattered->dir, &rec->normal) > 0);
}

t_material	material_new_lambertian(const t_color *albedo)
{
	t_material	mat;

	mat.scatter = lambertian_scatter;
	mat.albedo = *albedo;
	mat.fuzz = 0;
	return (mat);
}

t_material	material_new_metal(const t_color *albedo, double fuzz)
{
	t_material	mat;
	double		fuzz_val;

	mat.scatter = metal_scatter;
	mat.albedo = *albedo;
	fuzz_val = fuzz;
	if (fuzz_val < 1)
	{
		mat.fuzz = fuzz_val;
	}
	else
	{
		mat.fuzz = 1;
	}
	return (mat);
}
