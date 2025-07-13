/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_quadratic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:18:12 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:24:42 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cylinder_utils.h"

void	get_cyl_quadratic(const t_cylinder *cyl, const t_ray *r,
		t_quadratic *q)
{
	t_vec3	oc;
	double	card;
	double	caoc;

	oc = vec3_subtract(&r->orig, &cyl->center);
	card = vec3_dot(&r->dir, &cyl->axis);
	caoc = vec3_dot(&oc, &cyl->axis);
	q->a = vec3_length_squared(&r->dir) - card * card;
	q->b = 2 * (vec3_dot(&r->dir, &oc) - card * caoc);
	q->c = vec3_length_squared(&oc) - caoc * caoc - cyl->radius * cyl->radius;
}

bool	solve_quadratic(const t_quadratic *q, t_interval *ray_t,
		double *t)
{
	double	discriminant;
	double	root;
	double	sqrtd;

	discriminant = q->b * q->b - 4 * q->a * q->c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-q->b - sqrtd) / (2 * q->a);
	if (!interval_surrounds(ray_t, root))
	{
		root = (-q->b + sqrtd) / (2 * q->a);
		if (!interval_surrounds(ray_t, root))
			return (false);
	}
	*t = root;
	return (true);
}
