/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* cylinder.h                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_name <your_email@example.com>         +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/07/14 00:05:20 by your_name       #+#    #+#             */
/* Updated: 2025/07/14 00:05:20 by your_name       ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "hittable.h"
# include "material.h"

typedef struct s_cylinder
{
	t_hittable	hittable;
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_material	mat;
}				t_cylinder;

t_cylinder	*cylinder_new(t_point3 center, t_vec3 axis, double radius,
				double height, t_material mat);
bool		cylinder_hit(const t_hittable *self, const t_ray *r,
				t_interval ray_t, t_hit_record *rec);

#endif