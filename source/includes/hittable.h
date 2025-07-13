/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:44:05 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:15:19 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "interval.h"
# include "vectors/vec3.h"
# include <stdbool.h>

struct	s_ray;
struct	s_hittable;
struct	s_material;

typedef struct s_hit_record
{
	t_point3			p;
	t_vec3				normal;
	struct s_material	*mat;
	double				t;
	bool				front_face;
}						t_hit_record;

void					set_face_normal(t_hit_record *rec,
							const struct s_ray *r,
							const t_vec3 *outward_normal);

typedef struct s_hittable
{
	bool				(*hit)(const struct s_hittable * self,
		const struct s_ray * r, t_interval ray_t,
		t_hit_record * rec);
}						t_hittable;

#endif