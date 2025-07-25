/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:35:40 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/25 12:12:17 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_vec3	parse_vec3(char *str)
{
	char	**components;
	t_vec3	vec;

	components = ft_split(str, ',');
	vec = vec3_create(ft_atof(components[0]),
			ft_atof(components[1]),
			ft_atof(components[2]));
	ft_free_split(components);
	return (vec);
}

static t_color	parse_color(char *str)
{
	char	**components;
	t_color	color;

	components = ft_split(str, ',');
	color.e[0] = ft_atof(components[0]) / 255.0;
	color.e[1] = ft_atof(components[1]) / 255.0;
	color.e[2] = ft_atof(components[2]) / 255.0;
	ft_free_split(components);
	return (color);
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_vec3		position;
	t_vec3		normal;
	t_color		color;
	t_material	material;

	position = parse_vec3(tokens[1]);
	normal = parse_vec3(tokens[2]);
	color = parse_color(tokens[3]);
	material = material_new_lambertian(&color);
	hittable_list_add(scene->world,
		(t_hittable *)plane_new(position, normal, material));
}
