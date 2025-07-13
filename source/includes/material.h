/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:04:33 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:06:50 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"
# include "hittable.h"
# include "ray.h"
# include "vectors/vec3.h"
# include <stdbool.h>

struct	s_hit_record;

// New struct to hold scatter results
typedef struct s_scatter_record
{
	t_ray	scattered;
	t_color	attenuation;
}			t_scatter_record;

typedef struct s_material
{
	// Updated function pointer with fewer parameters
	bool	(*scatter)(const struct s_material * self,
		const t_ray * r_in, const struct s_hit_record * rec,
		t_scatter_record * srec);
	t_color	albedo;
	double	ir;
	double	fuzz;
}			t_material;

// Updated function prototypes
bool		lambertian_scatter(const t_material *self, const t_ray *r_in,
				const struct s_hit_record *rec, t_scatter_record *srec);
t_material	material_new_lambertian(const t_color *albedo);

bool		metal_scatter(const t_material *self, const t_ray *r_in,
				const struct s_hit_record *rec, t_scatter_record *srec);
t_material	material_new_metal(const t_color *albedo, double fuzz);

#endif