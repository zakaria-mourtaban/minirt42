/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phone_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:58:00 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/25 14:29:36 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static bool	is_in_shadow(t_scene *scene, t_ray *ray, double max_dist)
{
	return (hittable_list_hit((t_hittable *)scene->world, ray,
			interval_new(0, max_dist), &(t_hit_record){}));
}

static t_color	compute_ambient(t_scene *scene, t_hit_record *rec)
{
	t_color	ambient;

	ambient = vec3_scale(&scene->ambient_color, scene->ambient_ratio);
	return (vec3_multiply_components(&rec->mat->albedo, &ambient));
}

static t_ray	create_shadow_ray(t_hit_record *rec, t_vec3 *light_dir)
{
	t_vec3	offset;
	t_vec3	origin;

	offset = vec3_scale(&rec->normal, 1e-4);
	origin = vec3_add(&rec->p, &offset);
	return (ray_create(origin, *light_dir));
}

static t_color	compute_diffuse(t_scene *scene, t_hit_record *rec)
{
	t_vec3	light_dir;
	t_color	light_color;
	t_color	diffuse;
	t_ray	shadow_ray;
	double	diff;

	light_dir = vec3_subtract(&scene->light.position, &rec->p);
	shadow_ray = create_shadow_ray(rec, &light_dir);
	light_dir = vec3_unit_vector(&light_dir);
	if (is_in_shadow(scene, &shadow_ray, vec3_length(&light_dir)))
		return (vec3_create(0, 0, 0));
	diff = fmax(vec3_dot(&rec->normal, &light_dir), 0.0);
	light_color = (t_color){{1.0, 1.0, 1.0}};
	diffuse = vec3_scale(&light_color, diff * scene->light.brightness);
	return (vec3_multiply_components(&rec->mat->albedo, &diffuse));
}

t_color	phong_lighting(t_scene *scene, t_hit_record *rec)
{
	t_color	ambient;
	t_color	diffuse;

	ambient = compute_ambient(scene, rec);
	diffuse = compute_diffuse(scene, rec);
	return (vec3_add(&ambient, &diffuse));
}
