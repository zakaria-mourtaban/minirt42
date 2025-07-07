/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops4.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:19:58 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:19:58 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPS4_H
# define VEC3_OPS4_H

# include "vec3_defs.h"
# include <stdbool.h>

// Forward declarations to resolve implicit declaration errors
double	random_double(void);
double	random_double_range(double min, double max);
t_vec3	random_unit_vector(void);
t_vec3	random_on_hemisphere(const t_vec3 *normal);
t_vec3	vec3_reflect(const t_vec3 *v, const t_vec3 *n);
bool	vec3_near_zero(const t_vec3 *v);

#endif