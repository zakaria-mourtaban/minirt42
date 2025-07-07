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

/**
 * @struct t_ray
 * @brief Represents a 3D ray with an origin and a direction vector.
 *
 * @param orig The starting point of the ray (t_point3).
 * @param dir The direction vector of the ray (t_vec3).
 */
typedef struct s_ray
{
	t_point3			orig;
	t_vec3				dir;
}						t_ray;

/**
 * @brief Creates and returns a new ray.
 * This function acts as a constructor for a t_ray struct.
 *
 * @param origin The starting point for the new ray.
 * @param direction The direction vector for the new ray.
 * @return A new t_ray struct initialized with the given origin and direction.
 */
static inline t_ray	ray_create(const t_point3 origin, const t_vec3 direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

/**
 * @brief Calculates a point along the ray at a given distance 't'.
 * The formula used is P(t) = A + t*b,
	where A is the origin and b is the direction.
 *
 * @param r A pointer to the ray.
 * @param t The distance along the ray from the origin.
 * @return The calculated point (t_point3) in 3D space.
 */
static inline t_point3	ray_at(const t_ray *r, double t)
{
	t_vec3	scaled_dir;
	t_vec3	result;

	scaled_dir = vec3_scale(&r->dir, t);
	result = vec3_add(&r->orig, &scaled_dir);
	return (result);
}

#endif