/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:50:05 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/07 23:58:07 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "interval.h"
# include "ray.h"
# include <stdbool.h>

// Forward declaration
struct s_hittable;

typedef struct s_hit_record
{
	t_point3		p;
	t_vec3			normal;
	double			t;
	bool			front_face;
}					t_hit_record;

static inline void	set_face_normal(t_hit_record *rec, const t_ray *r,
		const t_vec3 *outward_normal)
{
	rec->front_face = vec3_dot(&r->dir, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec3_negate(outward_normal);
}

typedef struct s_hittable
{
	bool			(*hit)(const struct s_hittable *self, const t_ray *r,
					t_interval ray_t, t_hit_record *rec);
}					t_hittable;

#endif