/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2025/07/20 14:59:52 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/parsing/parse_file.h"

void	dispatch_element(char **tokens, t_scene *scene)
{
	if (!tokens[0])
		return ;
	if (!ft_strncmp(tokens[0], "A", 2))
		parse_ambient(tokens, scene);
	else if (!ft_strncmp(tokens[0], "C", 2))
		parse_camera(tokens, scene);
	else if (!ft_strncmp(tokens[0], "L", 2))
		parse_light(tokens, scene);
	else if (!ft_strncmp(tokens[0], "sp", 3))
		parse_sphere(tokens, scene);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		parse_plane(tokens, scene);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		parse_cylinder(tokens, scene);
}

void	parse_rt_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**tokens;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	line = ft_get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0' && line[0] != '\n')
		{
			tokens = ft_split(line, ' ');
			if (tokens && tokens[0])
				dispatch_element(tokens, scene);
			ft_free_split(tokens);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}
