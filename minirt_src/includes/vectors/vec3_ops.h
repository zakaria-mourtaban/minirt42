/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:09:55 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/06 00:09:57 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS_H
# define VEC3_OPS_H

# include "vec3_defs.h"

// Corresponds to the unary minus operator. Returns a new negated vector.
static inline t_vec3	vec3_negate(const t_vec3 *v)
{
	return (vec3_create(-v->e[0], -v->e[1], -v->e[2]));
}

// Access operators are not needed; you can directly access the array: v.e[i]
// For example: `my_vec.e[0] = 5.0;`

// In-place operations modify the vector pointed to by the first argument.
// These correspond to `operator+=`, `operator*=`, etc.

static inline void	vec3_add_inplace(t_vec3 *u, const t_vec3 *v)
{
	u->e[0] += v->e[0];
	u->e[1] += v->e[1];
	u->e[2] += v->e[2];
}

static inline void	vec3_scale_inplace(t_vec3 *v, double t)
{
	v->e[0] *= t;
	v->e[1] *= t;
	v->e[2] *= t;
}

static inline void	vec3_divide_inplace(t_vec3 *v, double t)
{
	vec3_scale_inplace(v, 1.0 / t);
}

static inline double	vec3_length_squared(const t_vec3 *v)
{
	return (v->e[0] * v->e[0] + v->e[1] * v->e[1] + v->e[2] * v->e[2]);
}

#endif