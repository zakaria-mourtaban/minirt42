/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3_defs.h"

t_vec3	vec3_create_zero(void)
{
	t_vec3	v;

	v.e[0] = 0;
	v.e[1] = 0;
	v.e[2] = 0;
	return (v);
}

t_vec3	vec3_create(double e0, double e1, double e2)
{
	t_vec3	v;

	v.e[0] = e0;
	v.e[1] = e1;
	v.e[2] = e2;
	return (v);
}

double	vec3_x(const t_vec3 *v)
{
	return (v->e[0]);
}

double	vec3_y(const t_vec3 *v)
{
	return (v->e[1]);
}

double	vec3_z(const t_vec3 *v)
{
	return (v->e[2]);
}
