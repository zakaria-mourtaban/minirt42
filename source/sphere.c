/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:29:20 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:29:21 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/sphere.h"
#include "includes/sphere_utils.h"
#include "includes/ray.h"
#include <stdlib.h>

t_sphere	*sphere_new(t_point3 center, double diameter, t_material mat)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->hittable.hit = sphere_hit;
	s->center = center;
	s->radius = diameter / 2.0;
	s->mat = mat;
	return (s);
}

void	setup_sphere_hit_record(t_hit_record *rec, const t_sphere *s,
		const t_ray *r, double root)
{
	t_vec3	outward_normal;
	t_vec3	sub_res;

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	sub_res = vec3_subtract(&rec->p, &s->center);
	outward_normal = vec3_divide(&sub_res, s->radius);
	set_face_normal(rec, r, &outward_normal);
	rec->mat = &((t_sphere *)s)->mat;
}

bool	sphere_hit(const t_hittable *self, const t_ray *r,
		t_interval ray_t, t_hit_record *rec)
{
	t_sphere_params	p;
	double			root;

	get_sphere_quadratic((const t_sphere *)self, r, &p);
	if (!solve_sphere_quadratic(&p, ray_t, &root))
		return (false);
	setup_sphere_hit_record(rec, (const t_sphere *)self, r, root);
	return (true);
}
