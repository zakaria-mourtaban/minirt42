/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:24:52 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:24:53 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cylinder_utils.h"
#include "includes/plane.h"

static bool	hit_single_cap(const t_cylinder *cyl, const t_ray *r,
		t_interval *ray_t, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_plane			cap_plane;
	t_vec3			dist_vec;

	cap_plane = (t_plane){.point = rec->p, .normal = rec->normal};
	if (plane_hit((t_hittable *)&cap_plane, r, *ray_t, &temp_rec))
	{
		dist_vec = vec3_subtract(&temp_rec.p, &rec->p);
		if (vec3_length_squared(&dist_vec) < cyl->radius * cyl->radius)
		{
			ray_t->max = temp_rec.t;
			*rec = temp_rec;
			rec->mat = &((t_cylinder *)cyl)->mat;
			return (true);
		}
	}
	return (false);
}

bool	check_caps(const t_cylinder *cyl, const t_ray *r, t_interval *ray_t,
		t_hit_record *rec)
{
	bool			hit_anything;
	t_vec3			offset;
	t_vec3			neg_axis;
	t_hit_record	cap_rec;

	hit_anything = false;
	offset = vec3_scale(&cyl->axis, -cyl->height / 2.0);
	cap_rec.p = vec3_add(&cyl->center, &offset);
	neg_axis = vec3_negate(&cyl->axis);
	cap_rec.normal = neg_axis;
	if (hit_single_cap(cyl, r, ray_t, &cap_rec))
	{
		*rec = cap_rec;
		hit_anything = true;
	}
	offset = vec3_scale(&cyl->axis, cyl->height / 2.0);
	cap_rec.p = vec3_add(&cyl->center, &offset);
	cap_rec.normal = cyl->axis;
	if (hit_single_cap(cyl, r, ray_t, &cap_rec))
	{
		*rec = cap_rec;
		hit_anything = true;
	}
	return (hit_anything);
}
