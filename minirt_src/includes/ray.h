/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:30:51 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/06 00:31:50 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vectors/vec3.h"

typedef struct s_ray
{
	t_point3			orig;
	t_vec3				dir;
} t_ray;

t_ray	ray_create(const t_point3 origin, const t_vec3 direction);
t_point3	ray_at(const t_ray *r, double t);

#endif