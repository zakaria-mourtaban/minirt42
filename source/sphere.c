/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:42:37 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 13:40:31 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ray.h"
#include "includes/sphere.h"
#include <stdlib.h>

t_sphere	*sphere_new(t_point3 center, double radius, t_material mat)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
	{
		return (NULL);
	}
	s->hittable.hit = sphere_hit;
	s->center = center;
	s->radius = radius;
	s->mat = mat;
	return (s);
}

static double	get_sphere_roots(double a, double h, double c, t_interval ray_t)
{
	double	discriminant;
	double	sqrtd;
	double	root;

	discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return (-1.0);
	}
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (!interval_surrounds(&ray_t, root))
	{
		root = (h + sqrtd) / a;
		if (!interval_surrounds(&ray_t, root))
		{
			return (-1.0);
		}
	}
	return (root);
}

bool	sphere_hit(const t_hittable *self, const t_ray *r,
		t_interval ray_t, t_hit_record *rec)
{
	t_sphere	*s;
	t_vec3		oc;
	double		a;
	double		h;
	double		c;
	double		root;
	t_vec3		outward_normal;
	t_vec3		sub_res;

	s = (t_sphere *)self;
	oc = vec3_subtract(&s->center, &r->orig);
	a = vec3_length_squared(&r->dir);
	h = vec3_dot(&r->dir, &oc);
	c = vec3_length_squared(&oc) - s->radius * s->radius;
	root = get_sphere_roots(a, h, c, ray_t);
	if (root == -1.0)
	{
		return (false);
	}
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	sub_res = vec3_subtract(&rec->p, &s->center);
	outward_normal = vec3_divide(&sub_res, s->radius);
	set_face_normal(rec, r, &outward_normal);
	rec->mat = &((t_sphere *)self)->mat;
	return (true);
}
