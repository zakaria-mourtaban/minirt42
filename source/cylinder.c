/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:22:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:22:04 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cylinder.h"
#include "includes/cylinder_utils.h"
#include "includes/ray.h"
#include <stdlib.h>
#include <math.h>

t_cylinder	*cylinder_new(t_cyl_params params, t_material mat)
{
	t_cylinder	*c;

	c = malloc(sizeof(t_cylinder));
	if (!c)
		return (NULL);
	c->hittable.hit = cylinder_hit;
	c->center = params.center;
	c->axis = vec3_unit_vector(&params.axis);
	c->radius = params.diameter / 2.0;
	c->height = params.height;
	c->mat = mat;
	return (c);
}

static void	setup_hit_record(t_hit_record *rec, const t_ray *r,
		const t_cylinder *cyl, t_hit_calc *calc)
{
	t_vec3	oc;
	t_vec3	proj;
	t_vec3	normal;

	rec->t = calc->t;
	rec->p = calc->hit_point;
	oc = vec3_subtract(&rec->p, &cyl->center);
	proj = vec3_scale(&cyl->axis, calc->m);
	normal = vec3_subtract(&oc, &proj);
	set_face_normal(rec, r, &normal);
	rec->mat = &((t_cylinder *)cyl)->mat;
}

static bool	process_body_hit(const t_ray *r, const t_cylinder *cyl,
		t_hit_record *rec, t_hit_calc *calc)
{
	t_vec3	hit_to_center;

	calc->hit_point = ray_at(r, calc->t);
	hit_to_center = vec3_subtract(&calc->hit_point, &cyl->center);
	calc->m = vec3_dot(&hit_to_center, &cyl->axis);
	if (calc->m >= -cyl->height / 2 && calc->m <= cyl->height / 2)
	{
		setup_hit_record(rec, r, cyl, calc);
		return (true);
	}
	return (false);
}

bool	cylinder_hit(const t_hittable *self, const t_ray *r,
		t_interval ray_t, t_hit_record *rec)
{
	const t_cylinder	*cyl;
	t_quadratic			q;
	t_hit_calc			calc;
	bool				hit_anything;

	cyl = (const t_cylinder *)self;
	get_cyl_quadratic(cyl, r, &q);
	hit_anything = check_caps(cyl, r, &ray_t, rec);
	if (solve_quadratic(&q, &ray_t, &calc.t))
	{
		if (process_body_hit(r, cyl, rec, &calc))
		{
			ray_t.max = calc.t;
			return (true);
		}
	}
	return (hit_anything);
}
