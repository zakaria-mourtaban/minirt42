#include "../includes/minirt.h"

void	parse_plane(char **tokens, t_scene *scene)
{
	char	**pos;
	char	**normal;
	char	**color;
	t_vec3	p;
	t_vec3	n;
	t_color	c;
	t_material	mat;

	pos = ft_split(tokens[1], ',');
	normal = ft_split(tokens[2], ',');
	color = ft_split(tokens[3], ',');
	p = vec3_create(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	n = vec3_create(ft_atof(normal[0]), ft_atof(normal[1]), ft_atof(normal[2]));
	c.e[0] = ft_atof(color[0]) / 255.0;
	c.e[1] = ft_atof(color[1]) / 255.0;
	c.e[2] = ft_atof(color[2]) / 255.0;
	mat = material_new_lambertian(&c);
	hittable_list_add(scene->world, (t_hittable *)plane_new(p, n, mat));
	ft_free_split(pos);
	ft_free_split(normal);
	ft_free_split(color);
} 