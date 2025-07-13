/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* material.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_name <your_email@example.com>         +#+  +:+       +#+        */
/*+#+#+#+#+#+   +#+           */
/* Created: 2025/07/08 01:10:53 by zmourtab          #+#    #+#             */
/* Updated: 2025/07/14 01:00:00 by your_name       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/vectors/vec3.h"
#include "includes/random.h"

// For a simple lighting model, a Lambertian surface does not scatter rays.
// Its color is determined by the direct light it receives.
bool	lambertian_scatter(const t_material *self, const t_ray *r_in,
		const struct s_hit_record *rec, t_color *attenuation,
		t_ray *scattered)
{
	(void)self;
	(void)r_in;
	(void)rec;
	(void)attenuation;
	(void)scattered;
	return (false);
}

bool	metal_scatter(const t_material *self, const t_ray *r_in,
		const struct s_hit_record *rec, t_color *attenuation,
		t_ray *scattered)
{
	t_vec3	reflected;
	t_vec3	fuzzed_reflected;
	t_vec3	rand_unit;
	t_vec3	unit_dir;

	unit_dir = vec3_unit_vector(&r_in->dir);
	reflected = vec3_reflect(&unit_dir, &rec->normal);
	rand_unit = random_unit_vector();
	vec3_scale_inplace(&rand_unit, self->fuzz);
	fuzzed_reflected = vec3_add(&reflected, &rand_unit);
	*scattered = ray_create(rec->p, fuzzed_reflected);
	*attenuation = self->albedo;
	return (vec3_dot(&scattered->dir, &rec->normal) > 0);
}

// ... (material constructors remain the same) ...
t_material	material_new_lambertian(const t_color *albedo)
{
	t_material	mat;

	mat.scatter = lambertian_scatter;
	mat.albedo = *albedo;
	mat.fuzz = 0;
	mat.ir = 0;
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
	mat.ir = 0;
	return (mat);
}