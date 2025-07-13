/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:21:49 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:21:50 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_UTILS_H
# define CYLINDER_UTILS_H

# include "cylinder.h"

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
}				t_quadratic;

// New struct to hold hit calculation variables to respect the 5-var rule.
typedef struct s_hit_calc
{
	double		t;
	double		m;
	t_point3	hit_point;
}				t_hit_calc;

void	get_cyl_quadratic(const t_cylinder *cyl, const t_ray *r,
			t_quadratic *q);
bool	solve_quadratic(const t_quadratic *q, t_interval *ray_t,
			double *t);
bool	check_caps(const t_cylinder *cyl, const t_ray *r, t_interval *ray_t,
			t_hit_record *rec);

#endif