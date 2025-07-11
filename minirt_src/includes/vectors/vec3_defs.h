/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_defs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:09:42 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 09:54:01 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_DEFS_H
# define VEC3_DEFS_H
# include <math.h>

typedef struct vec3
{
	double				e[3];
}	t_vec3;

typedef t_vec3			t_point3;

t_vec3	vec3_create_zero(void);
t_vec3	vec3_create(double e0, double e1, double e2);
double	vec3_x(const t_vec3 *v);
double	vec3_y(const t_vec3 *v);
double	vec3_z(const t_vec3 *v);

#endif