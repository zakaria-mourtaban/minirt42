/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops2.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:10:13 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:10:17 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS2_H
# define VEC3_OPS2_H

# include "vec3_defs.h"
# include "vec3_ops.h"

double	vec3_length(const t_vec3 *v);
void	vec3_subtract_inplace(t_vec3 *u, const t_vec3 *v);
t_vec3	vec3_add(const t_vec3 *u, const t_vec3 *v);
t_vec3	vec3_subtract(const t_vec3 *u, const t_vec3 *v);
t_vec3	vec3_multiply_components(const t_vec3 *u, const t_vec3 *v);

#endif