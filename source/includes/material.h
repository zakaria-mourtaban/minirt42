/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:10:32 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 13:36:25 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "hittable.h"
# include "ray.h"
# include "vectors/vec3.h"
# include <stdbool.h>

struct s_hit_record;

typedef struct s_material
{
	bool	(*scatter)(const struct s_material *self, const t_ray *r_in,
			const struct s_hit_record *rec, t_color *attenuation,
			t_ray *scattered);
	t_color	albedo;
	double	fuzz;
}			t_material;

bool		lambertian_scatter(const t_material *self, const t_ray *r_in,
				const struct s_hit_record *rec, t_color *attenuation,
				t_ray *scattered);
t_material	material_new_lambertian(const t_color *albedo);

bool		metal_scatter(const t_material *self, const t_ray *r_in,
				const struct s_hit_record *rec, t_color *attenuation,
				t_ray *scattered);
t_material	material_new_metal(const t_color *albedo, double fuzz);

#endif