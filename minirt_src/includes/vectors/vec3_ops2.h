/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:10:13 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/06 00:10:15 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS2_H
# define VEC3_OPS2_H

# include "vec3_defs.h"
# include "vec3_ops.h"

static inline double	vec3_length(const t_vec3 *v)
{
	return (sqrt(vec3_length_squared(v)));
}

// --- Vector Utility Functions ---
// Global operator overloads are replaced with named functions.

// Functions that return a new vector result
static inline t_vec3	vec3_add(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_create(u->e[0] + v->e[0], u->e[1] + v->e[1], u->e[2]
			+ v->e[2]));
}

static inline t_vec3	vec3_subtract(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_create(u->e[0] - v->e[0], u->e[1] - v->e[1], u->e[2]
			- v->e[2]));
}

// Note: This is component-wise multiplication (Hadamard product)
static inline t_vec3	vec3_multiply_components(const t_vec3 *u,
		const t_vec3 *v)
{
	return (vec3_create(u->e[0] * v->e[0], u->e[1] * v->e[1], u->e[2]
			* v->e[2]));
}

#endif