/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3_ops2.h"
#include "includes/vectors/vec3_defs.h"
#include "includes/vectors/vec3_ops.h"
#include <math.h>

double	vec3_length(const t_vec3 *v)
{
	return (sqrt(vec3_length_squared(v)));
}

void	vec3_subtract_inplace(t_vec3 *u, const t_vec3 *v)
{
	u->e[0] -= v->e[0];
	u->e[1] -= v->e[1];
	u->e[2] -= v->e[2];
}

t_vec3	vec3_add(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_create(u->e[0] + v->e[0], u->e[1] + v->e[1], u->e[2]
			+ v->e[2]));
}

t_vec3	vec3_subtract(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_create(u->e[0] - v->e[0], u->e[1] - v->e[1], u->e[2]
			- v->e[2]));
}

t_vec3	vec3_multiply_components(const t_vec3 *u, const t_vec3 *v)
{
	return (vec3_create(u->e[0] * v->e[0], u->e[1] * v->e[1], u->e[2]
			* v->e[2]));
}
