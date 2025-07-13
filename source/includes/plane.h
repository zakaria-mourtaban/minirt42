/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* plane.h                                            :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_name <your_email@example.com>         +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/07/14 00:05:00 by your_name       #+#    #+#             */
/* Updated: 2025/07/14 00:05:00 by your_name       ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "hittable.h"
# include "material.h"

typedef struct s_plane
{
	t_hittable	hittable;
	t_point3	point;
	t_vec3		normal;
	t_material	mat;
}				t_plane;

t_plane	*plane_new(t_point3 point, t_vec3 normal, t_material mat);
bool	plane_hit(const t_hittable *self, const t_ray *r,
			t_interval ray_t, t_hit_record *rec);

#endif