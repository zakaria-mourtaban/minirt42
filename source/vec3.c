/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:30:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 11:30:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3.h"

t_vec3	vec3_reflect(const t_vec3 *v, const t_vec3 *n)
{
	t_vec3	result;
	double	dot_vn;

	dot_vn = vec3_dot(v, n);
	result = vec3_scale(n, 2 * dot_vn);
	result = vec3_subtract(v, &result);
	return (result);
}

bool	vec3_near_zero(const t_vec3 *v)
{
	double	s;

	s = 1e-8;
	return (fabs(v->e[0]) < s && fabs(v->e[1]) < s && fabs(v->e[2]) < s);
}
