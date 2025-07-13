/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_quadratic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:28:59 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:29:03 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/sphere_utils.h"

void	get_sphere_quadratic(const t_sphere *s, const t_ray *r,
		t_sphere_params *p)
{
	p->oc = vec3_subtract(&r->orig, &s->center);
	p->a = vec3_length_squared(&r->dir);
	p->b = 2.0 * vec3_dot(&p->oc, &r->dir);
	p->c = vec3_length_squared(&p->oc) - s->radius * s->radius;
	p->discriminant = p->b * p->b - 4 * p->a * p->c;
}

bool	solve_sphere_quadratic(t_sphere_params *p, t_interval ray_t,
		double *root)
{
	double	sqrtd;
	double	temp_root;

	if (p->discriminant < 0)
		return (false);
	sqrtd = sqrt(p->discriminant);
	temp_root = (-p->b - sqrtd) / (2.0 * p->a);
	if (!interval_surrounds(&ray_t, temp_root))
	{
		temp_root = (-p->b + sqrtd) / (2.0 * p->a);
		if (!interval_surrounds(&ray_t, temp_root))
			return (false);
	}
	*root = temp_root;
	return (true);
}
