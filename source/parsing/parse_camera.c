/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:03:50 by mkraytem          #+#    #+#             */
/*   Updated: 2025/08/20 14:48:31 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#define M_PI	3.14159265358979323846

static	void	parse_camera_position(char **tokens, t_camera *camera)
{
	char	**pos;

	pos = ft_split(tokens[1], ',');
	camera->lookfrom = vec3_create(ft_atof(pos[0]),
			ft_atof(pos[1]), ft_atof(pos[2]));
	ft_free_split(pos);
}

static	void	parse_camera_orientation(char **tokens, t_camera *camera)
{
	char	**orient;

	orient = ft_split(tokens[2], ',');
	camera->lookat = vec3_create((ft_atof(orient[0]) * 180),
			(ft_atof(orient[1]) * 180), (ft_atof(orient[2]) * 180));
	ft_free_split(orient);
}

static	void	set_camera_angles(t_camera *camera)
{
	double	dx;
	double	dy;
	double	dz;
	double	dir_len;

	dx = camera->lookat.e[0] - camera->lookfrom.e[0];
	dy = camera->lookat.e[1] - camera->lookfrom.e[1];
	dz = camera->lookat.e[2] - camera->lookfrom.e[2];
	camera->yaw = atan2(dz, dx);
	dir_len = sqrt(dx * dx + dy * dy + dz * dz);
	if (dir_len != 0)
		camera->pitch = asin(dy / dir_len);
	else
		camera->pitch = 0;
}

void	parse_camera(char **tokens, t_scene *scene)
{
	double	fov;
	t_vec3	look_dir;
	double	dot;

	parse_camera_position(tokens, scene->camera);
	parse_camera_orientation(tokens, scene->camera);
	fov = ft_atof(tokens[3]);
	scene->camera->vfov = -fov * 0.075;
	scene->camera->aspect_ratio = 16.0 / 9.0;
	scene->camera->image_width = 800;
	look_dir = vec3_subtract(&scene->camera->lookat, &scene->camera->lookfrom);
	look_dir = vec3_unit_vector(&look_dir);
	dot = fabs(look_dir.e[0] * 0 + look_dir.e[1] * 1 + look_dir.e[2] * 0);
	if (dot > 0.999)
		scene->camera->vup = vec3_create(1, 0, 0);
	else
		scene->camera->vup = vec3_create(0, 1, 0);
	set_camera_angles(scene->camera);
}
