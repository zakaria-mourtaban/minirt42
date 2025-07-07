/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:42:37 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:43:17 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ray.h"
#include "./includes/sphere.h"
#include <stdlib.h>

t_sphere	*sphere_new(t_point3 center, double radius)
{
	t_sphere	*s;

	s = (t_sphere *)malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->center = center;
	s->radius = fmax(0, radius);
	s->hittable.hit = sphere_hit;
	return (s);
}

bool	sphere_hit(const t_hittable *self, const t_ray *r, t_interval ray_t,
		t_hit_record *rec)
{
	t_sphere *s;
	t_vec3 oc;
	double a;
	double h;
	double c;
	double discriminant;
	double root;
	double sqrtd;
	t_vec3 outward_normal;
	t_vec3 sub_res;

	s = (t_sphere *)self;
	oc = vec3_subtract(&s->center, &r->orig);
	a = vec3_length_squared(&r->dir);
	h = vec3_dot(&r->dir, &oc);
	c = vec3_length_squared(&oc) - s->radius * s->radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (!interval_surrounds(&ray_t, root))
	{
		root = (h + sqrtd) / a;
		if (!interval_surrounds(&ray_t, root))
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	sub_res = vec3_subtract(&rec->p, &s->center);
	outward_normal = vec3_divide(&sub_res, s->radius);
	set_face_normal(rec, r, &outward_normal);
	return (true);
}