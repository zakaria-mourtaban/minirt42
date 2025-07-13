/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* cylinder.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_name <your_email@example.com>         +#+  +:+       +#+        */
/*+#+#+#+#+#+   +#+           */
/* Created: 2025/07/14 00:05:30 by your_name       #+#    #+#             */
/* Updated: 2025/07/14 00:20:00 by your_name       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "includes/cylinder.h"
#include "includes/ray.h"
#include "includes/plane.h" // <-- MISSING INCLUDE
#include <stdlib.h>
#include <math.h>

static bool	check_caps(const t_cylinder *cyl, const t_ray *r, t_interval *ray_t,
		t_hit_record *rec);

t_cylinder	*cylinder_new(t_point3 center, t_vec3 axis, double radius,
		double height, t_material mat)
{
	t_cylinder	*c;

	c = malloc(sizeof(t_cylinder));
	if (!c)
		return (NULL);
	c->hittable.hit = cylinder_hit;
	c->center = center;
	c->axis = vec3_unit_vector(&axis);
	c->radius = radius / 2.0;
	c->height = height;
	c->mat = mat;
	return (c);
}

static void	get_cyl_quadratic(const t_cylinder *cyl, const t_ray *r, double *a,
		double *b, double *c)
{
	t_vec3	oc;
	double	card;
	double	caoc;

	oc = vec3_subtract(&r->orig, &cyl->center);
	card = vec3_dot(&r->dir, &cyl->axis);
	caoc = vec3_dot(&oc, &cyl->axis);
	*a = vec3_length_squared(&r->dir) - card * card;
	*b = 2 * (vec3_dot(&r->dir, &oc) - card * caoc);
	*c = vec3_length_squared(&oc) - caoc * caoc - cyl->radius * cyl->radius;
}

static bool	solve_quadratic(double a, double b, double c, t_interval *ray_t,
		double *t)
{
	double	discriminant;
	double	root;
	double	sqrtd;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / (2 * a);
	if (!interval_surrounds(ray_t, root))
	{
		root = (-b + sqrtd) / (2 * a);
		if (!interval_surrounds(ray_t, root))
			return (false);
	}
	*t = root;
	return (true);
}

bool	cylinder_hit(const t_hittable *self, const t_ray *r, t_interval ray_t,
		t_hit_record *rec)
{
	const t_cylinder	*cyl;
	double				a;
	double				b;
	double				c;
	double				t;
	double				m;
	t_point3			hit_point;
	t_vec3				oc;
	t_vec3				proj;
	t_vec3				normal;
	bool				hit_anything;

	cyl = (const t_cylinder *)self;
	get_cyl_quadratic(cyl, r, &a, &b, &c);
	hit_anything = check_caps(cyl, r, &ray_t, rec);
	if (solve_quadratic(a, b, c, &ray_t, &t))
	{
		hit_point = ray_at(r, t);
		oc = vec3_subtract(&hit_point, &cyl->center);
		m = vec3_dot(&oc, &cyl->axis);
		if (m >= -cyl->height / 2 && m <= cyl->height / 2)
		{
			hit_anything = true;
			ray_t.max = t;
			rec->t = t;
			rec->p = hit_point;
			proj = vec3_scale(&cyl->axis, m);
			normal = vec3_subtract(&oc, &proj);
			set_face_normal(rec, r, &normal);
			rec->mat = &((t_cylinder *)self)->mat;
		}
	}
	return (hit_anything);
}

static bool	check_caps(const t_cylinder *cyl, const t_ray *r, t_interval *ray_t,
		t_hit_record *rec)
{
	bool			hit_anything;
	t_hit_record	temp_rec;
	t_plane			cap;
	t_point3		cap_center;
	t_vec3			offset;
	t_vec3			dist_vec;

	hit_anything = false;
	offset = vec3_scale(&cyl->axis, -cyl->height / 2.0);
	cap_center = vec3_add(&cyl->center, &offset);
	cap = (t_plane){.point = cap_center, .normal = vec3_negate(&cyl->axis)};
	if (plane_hit((t_hittable *)&cap, r, *ray_t, &temp_rec))
	{
		dist_vec = vec3_subtract(&temp_rec.p, &cap_center);
		if (vec3_length_squared(&dist_vec) < cyl->radius * cyl->radius)
		{
			hit_anything = true;
			ray_t->max = temp_rec.t;
			*rec = temp_rec;
			rec->mat = &((t_cylinder *)cyl)->mat;
		}
	}
	offset = vec3_scale(&cyl->axis, cyl->height / 2.0);
	cap_center = vec3_add(&cyl->center, &offset);
	cap = (t_plane){.point = cap_center, .normal = cyl->axis};
	if (plane_hit((t_hittable *)&cap, r, *ray_t, &temp_rec))
	{
		dist_vec = vec3_subtract(&temp_rec.p, &cap_center);
		if (vec3_length_squared(&dist_vec) < cyl->radius * cyl->radius)
		{
			hit_anything = true;
			ray_t->max = temp_rec.t;
			*rec = temp_rec;
			rec->mat = &((t_cylinder *)cyl)->mat;
		}
	}
	return (hit_anything);
}