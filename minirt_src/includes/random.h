/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

# include "vectors/vec3_defs.h"
# include <stdbool.h>

double	random_double(void);
double	random_double_range(double min, double max);
t_vec3	random_unit_vector(void);
t_vec3	random_on_hemisphere(const t_vec3 *normal);

#endif