#include "../includes/minirt.h"

void	parse_camera(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**orient;
	double	fov;

	pos = ft_split(tokens[1], ',');
	scene->camera->lookfrom = vec3_create(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	ft_free_split(pos);
	orient = ft_split(tokens[2], ',');
	scene->camera->lookat = vec3_create(ft_atof(orient[0]), ft_atof(orient[1]), ft_atof(orient[2]));
	ft_free_split(orient);
	fov = ft_atof(tokens[3]);
	scene->camera->vfov = fov;
	// Ensure all required fields are set as in initialize_scene
	scene->camera->aspect_ratio = 16.0 / 9.0;
	scene->camera->image_width = 800;
	scene->camera->vup = vec3_create(0, 1, 0);
	double dx = scene->camera->lookat.e[0] - scene->camera->lookfrom.e[0];
	double dy = scene->camera->lookat.e[1] - scene->camera->lookfrom.e[1];
	double dz = scene->camera->lookat.e[2] - scene->camera->lookfrom.e[2];
	scene->camera->yaw = atan2(dz, dx);
	double dir_len = sqrt(dx * dx + dy * dy + dz * dz);
	if (dir_len != 0)
		scene->camera->pitch = asin(dy / dir_len);
	else
		scene->camera->pitch = 0;
} 