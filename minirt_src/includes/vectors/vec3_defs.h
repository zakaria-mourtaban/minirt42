/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_defs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:09:42 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/06 00:09:46 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_DEFS_H
# define VEC3_DEFS_H
# include <math.h>

// In C, we use a struct instead of a class.
// By convention, we also typedef it to avoid writing `struct vec3` everywhere.
typedef struct vec3
{
	double				e[3];
}						t_vec3;

// point3 is just an alias for vec3, useful for geometric clarity.
typedef t_vec3			t_point3;

// --- "Constructors" ---
// C doesn't have constructors, so we create functions that return a new vec3.

// Returns a zero vector
static inline t_vec3	vec3_create_zero(void)
{
	t_vec3	v;

	v.e[0] = 0;
	v.e[1] = 0;
	v.e[2] = 0;
	return (v);
}

// Returns a vector with specified components
static inline t_vec3	vec3_create(double e0, double e1, double e2)
{
	t_vec3	v;

	v.e[0] = e0;
	v.e[1] = e1;
	v.e[2] = e2;
	return (v);
}

// --- "Member Functions" ---
// Member functions are replaced by global functions that take a pointer
// to the struct as the first argument.

static inline double	vec3_x(const t_vec3 *v)
{
	return (v->e[0]);
}

static inline double	vec3_y(const t_vec3 *v)
{
	return (v->e[1]);
}

static inline double	vec3_z(const t_vec3 *v)
{
	return (v->e[2]);
}

#endif