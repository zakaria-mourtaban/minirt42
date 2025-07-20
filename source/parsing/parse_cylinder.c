#include "../includes/minirt.h"

void	parse_cylinder(char **tokens, t_scene *scene)
{
	char	**center;
	char	**axis;
	char	**color;
	double	diameter;
	double	height;
	t_color	c;
	t_cyl_params params;
	t_material mat;

	center = ft_split(tokens[1], ',');
	axis = ft_split(tokens[2], ',');
	color = ft_split(tokens[5], ',');
	diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
	params.center = vec3_create(ft_atof(center[0]), ft_atof(center[1]), ft_atof(center[2]));
	params.axis = vec3_create(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]));
	params.diameter = diameter;
	params.height = height;
	c.e[0] = ft_atof(color[0]) / 255.0;
	c.e[1] = ft_atof(color[1]) / 255.0;
	c.e[2] = ft_atof(color[2]) / 255.0;
	mat = material_new_lambertian(&c);
	hittable_list_add(scene->world, (t_hittable *)cylinder_new(params, mat));
	ft_free_split(center);
	ft_free_split(axis);
	ft_free_split(color);
}