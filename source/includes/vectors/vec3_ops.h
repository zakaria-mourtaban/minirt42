/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:09:55 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:29:16 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS_H
# define VEC3_OPS_H

# include "vec3_defs.h"

t_vec3	vec3_negate(const t_vec3 *v);
void	vec3_add_inplace(t_vec3 *u, const t_vec3 *v);
void	vec3_scale_inplace(t_vec3 *v, double t);
void	vec3_divide_inplace(t_vec3 *v, double t);
double	vec3_length_squared(const t_vec3 *v);

#endif