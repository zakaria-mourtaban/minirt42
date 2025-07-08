/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3_ops.h"
#include "includes/vectors/vec3_defs.h"

t_vec3	vec3_negate(const t_vec3 *v)
{
	return (vec3_create(-v->e[0], -v->e[1], -v->e[2]));
}

void	vec3_add_inplace(t_vec3 *u, const t_vec3 *v)
{
	u->e[0] += v->e[0];
	u->e[1] += v->e[1];
	u->e[2] += v->e[2];
}

void	vec3_scale_inplace(t_vec3 *v, double t)
{
	v->e[0] *= t;
	v->e[1] *= t;
	v->e[2] *= t;
}

void	vec3_divide_inplace(t_vec3 *v, double t)
{
	vec3_scale_inplace(v, 1.0 / t);
}

double	vec3_length_squared(const t_vec3 *v)
{
	return (v->e[0] * v->e[0] + v->e[1] * v->e[1] + v->e[2] * v->e[2]);
}
