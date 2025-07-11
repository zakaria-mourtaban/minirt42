/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3_ops3.h"
#include "includes/vectors/vec3_defs.h"
#include "includes/vectors/vec3_ops.h"
#include "includes/vectors/vec3_ops2.h"

t_vec3	vec3_scale(const t_vec3 *v, double t)
{
	return (vec3_create(t * v->e[0], t * v->e[1], t * v->e[2]));
}

t_vec3	vec3_divide(const t_vec3 *v, double t)
{
	return (vec3_scale(v, 1.0 / t));
}

double	vec3_dot(const t_vec3 *u, const t_vec3 *v)
{
	return (u->e[0] * v->e[0] + u->e[1] * v->e[1] + u->e[2] * v->e[2]);
}

t_vec3	vec3_cross(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_create(u->e[1] * v->e[2] - u->e[2] * v->e[1],
			u->e[2] * v->e[0] - u->e[0] * v->e[2],
			u->e[0] * v->e[1] - u->e[1] * v->e[0]));
}

t_vec3	vec3_unit_vector(const t_vec3 *v)
{
	double	len;

	len = vec3_length(v);
	return (vec3_divide(v, len));
}
