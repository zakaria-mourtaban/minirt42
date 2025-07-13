/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:28:44 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:28:45 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_UTILS_H
# define SPHERE_UTILS_H

# include "sphere.h"

// Struct to hold the parameters for the sphere intersection quadratic equation.
typedef struct s_sphere_params
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
}				t_sphere_params;

// Function prototypes for the new helper functions.
void	get_sphere_quadratic(const t_sphere *s, const t_ray *r,
			t_sphere_params *p);
bool	solve_sphere_quadratic(t_sphere_params *p, t_interval ray_t,
			double *root);
void	setup_sphere_hit_record(t_hit_record *rec, const t_sphere *s,
			const t_ray *r, double root);

#endif