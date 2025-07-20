#include "../includes/minirt.h"

void	parse_light(char **tokens, t_scene *scene)
{
	char	**pos;
	double	brightness;

	pos = ft_split(tokens[1], ',');
	scene->light.position = vec3_create(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	ft_free_split(pos);
	brightness = ft_atof(tokens[2]);
	scene->light.brightness = brightness;
} 