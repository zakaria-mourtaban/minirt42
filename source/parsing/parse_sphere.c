/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:35:43 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/20 20:02:22 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_sphere(char **tokens, t_scene *scene)
{
	char		**center;
	char		**color;
	double		diameter;
	t_color		c;
	t_material	mat;

	center = ft_split(tokens[1], ',');
	color = ft_split(tokens[3], ',');
	diameter = ft_atof(tokens[2]);
	c.e[0] = ft_atof(color[0]) / 255.0;
	c.e[1] = ft_atof(color[1]) / 255.0;
	c.e[2] = ft_atof(color[2]) / 255.0;
	mat = material_new_lambertian(&c);
	hittable_list_add(scene->world, (t_hittable *)sphere_new(
			vec3_create(ft_atof(center[0]),
				ft_atof(center[1]), ft_atof(center[2])),
			diameter, mat));
	ft_free_split(center);
	ft_free_split(color);
}
