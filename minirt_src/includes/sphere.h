/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:12:31 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:12:31 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "hittable.h"
# include "material.h"
# include <math.h>

typedef struct s_sphere
{
	t_hittable	hittable;
	t_point3	center;
	double		radius;
	t_material	mat;
} t_sphere;

t_sphere		*sphere_new(t_point3 center, double radius, t_material mat);
bool			sphere_hit(const t_hittable *self, const t_ray *r,
					t_interval ray_t, t_hit_record *rec);

#endif