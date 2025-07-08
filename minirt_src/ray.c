/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray.h"
#include "includes/vectors/vec3.h"

t_ray	ray_create(const t_point3 origin, const t_vec3 direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

t_point3	ray_at(const t_ray *r, double t)
{
	t_vec3	scaled_dir;
	t_vec3	result;

	scaled_dir = vec3_scale(&r->dir, t);
	result = vec3_add(&r->orig, &scaled_dir);
	return (result);
}
