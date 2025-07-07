/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:44:05 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:44:09 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "interval.h"
# include "vectors/vec3.h" // Keep this for t_vec3
# include <stdbool.h>

// Forward declarations to break circular dependencies
struct s_ray;
struct s_hittable;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	bool		front_face;
}				t_hit_record;

// Function Prototypes
void			set_face_normal(t_hit_record *rec, const struct s_ray *r,
					const t_vec3 *outward_normal);

typedef struct s_hittable
{
	bool		(*hit)(const struct s_hittable *self, const struct s_ray *r,
				t_interval ray_t, t_hit_record *rec);
}				t_hittable;

#endif