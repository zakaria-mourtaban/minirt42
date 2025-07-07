/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:19:49 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:20:42 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3.h"
#include <math.h>

t_vec3	vec3_reflect(const t_vec3 *v, const t_vec3 *n)
{
	t_vec3	scaled_n;
	double	dot_vn;

	dot_vn = vec3_dot(v, n);
	scaled_n = *n;
	vec3_scale_inplace(&scaled_n, 2 * dot_vn);
	return (vec3_subtract(v, &scaled_n));
}

bool	vec3_near_zero(const t_vec3 *v)
{
	double s;

	// Return true if the vector is close to zero in all dimensions.
	s = 1e-8;
	return (fabs(v->e[0]) < s && fabs(v->e[1]) < s && fabs(v->e[2]) < s);
}