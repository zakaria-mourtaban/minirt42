/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* plane.c                                            :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_name <your_email@example.com>         +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/07/14 00:05:10 by your_name       #+#    #+#             */
/* Updated: 2025/07/14 00:05:10 by your_name       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "includes/plane.h"
#include "includes/ray.h"
#include <stdlib.h>

t_plane	*plane_new(t_point3 point, t_vec3 normal, t_material mat)
{
	t_plane	*p;

	p = malloc(sizeof(t_plane));
	if (!p)
		return (NULL);
	p->hittable.hit = plane_hit;
	p->point = point;
	p->normal = vec3_unit_vector(&normal);
	p->mat = mat;
	return (p);
}

bool	plane_hit(const t_hittable *self, const t_ray *r,
		t_interval ray_t, t_hit_record *rec)
{
	const t_plane	*p = (const t_plane *)self;
	double			denom;
	t_vec3			p0_to_ray_orig;
	double			t;

	denom = vec3_dot(&p->normal, &r->dir);
	if (fabs(denom) < 1e-6)
		return (false);
	p0_to_ray_orig = vec3_subtract(&p->point, &r->orig);
	t = vec3_dot(&p0_to_ray_orig, &p->normal) / denom;
	if (!interval_contains(&ray_t, t))
		return (false);
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->mat = &((t_plane *)self)->mat;
	set_face_normal(rec, r, &p->normal);
	return (true);
}