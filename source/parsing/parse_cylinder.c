/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:35:29 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/20 15:02:55 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	parse_cylinder_params(char **tokens, t_cyl_params *params)
{
	char	**center;
	char	**axis;
	double	diameter;
	double	height;

	center = ft_split(tokens[1], ',');
	axis = ft_split(tokens[2], ',');
	diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
	params->center = vec3_create(ft_atof(center[0]),
		ft_atof(center[1]), ft_atof(center[2]));
	params->axis = vec3_create(ft_atof(axis[0]),
		ft_atof(axis[1]), ft_atof(axis[2]));
	params->diameter = diameter;
	params->height = height;
	ft_free_split(center);
	ft_free_split(axis);
}

static void	parse_cylinder_color_mat(char **tokens, t_color *c, t_material *mat)
{
	char	**color;

	color = ft_split(tokens[5], ',');
	c->e[0] = ft_atof(color[0]) / 255.0;
	c->e[1] = ft_atof(color[1]) / 255.0;
	c->e[2] = ft_atof(color[2]) / 255.0;
	*mat = material_new_lambertian(c);
	ft_free_split(color);
}

void	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cyl_params	params;
	t_color		c;
	t_material	mat;

	parse_cylinder_params(tokens, &params);
	parse_cylinder_color_mat(tokens, &c, &mat);
	hittable_list_add(scene->world,
		(t_hittable *)cylinder_new(params, mat));
}