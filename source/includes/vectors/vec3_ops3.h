/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:10:25 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:34:32 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS3_H
# define VEC3_OPS3_H

# include "vec3_defs.h"
# include "vec3_ops.h"
# include "vec3_ops2.h"

t_vec3	vec3_scale(const t_vec3 *v, double t);
t_vec3	vec3_divide(const t_vec3 *v, double t);
double	vec3_dot(const t_vec3 *u, const t_vec3 *v);
t_vec3	vec3_cross(const t_vec3 *u, const t_vec3 *v);
t_vec3	vec3_unit_vector(const t_vec3 *v);
t_vec3	vec3_unit(t_vec3 v);

#endif