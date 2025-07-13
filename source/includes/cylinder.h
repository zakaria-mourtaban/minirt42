/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:20:17 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:20:18 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "hittable.h"
# include "material.h"

// Struct to group the cylinder's geometric parameters.
typedef struct s_cyl_params
{
	t_point3	center;
	t_vec3		axis;
	double		diameter;
	double		height;
}				t_cyl_params;

typedef struct s_cylinder
{
	t_hittable	hittable;
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_material	mat;
}				t_cylinder;

// The constructor now takes the params struct, reducing its arguments to 2.
t_cylinder	*cylinder_new(t_cyl_params params, t_material mat);

bool		cylinder_hit(const t_hittable *self, const t_ray *r,
				t_interval ray_t, t_hit_record *rec);

#endif