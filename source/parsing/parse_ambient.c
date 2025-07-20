#include "../includes/minirt.h"

void	parse_ambient(char **tokens, t_scene *scene)
{
	double	ratio;
	char	**colors;

	ratio = ft_atof(tokens[1]);
	colors = ft_split(tokens[2], ',');
	scene->ambient_ratio = ratio;
	scene->ambient_color.e[0] = ft_atof(colors[0]) / 255.0;
	scene->ambient_color.e[1] = ft_atof(colors[1]) / 255.0;
	scene->ambient_color.e[2] = ft_atof(colors[2]) / 255.0;
	ft_free_split(colors);
} 