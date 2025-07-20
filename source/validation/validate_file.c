/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2024/07/14 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/validation/validate_file.h"
#include "../includes/validation/validation_utils.h"
#include "../includes/minirt.h"
#include <stdio.h>

static void	validate_ambient(char **tokens, int count, int *a_flag)
{
	double	ratio;

	if (count != 3)
		error_exit("Ambient: wrong number of arguments (expected 3)\n");
	if (*a_flag)
		error_exit("Error: Multiple ambient lights defined (only one allowed)\n");
	*a_flag = 1;
	validate_numeric_string(tokens[1]);
	ratio = ft_atof(tokens[1]);
	validate_ratio(ratio);
	validate_color_format(tokens[2]);
	printf("Validated Ambient: ratio=%.2f, color=%s\n", ratio, tokens[2]);
}

static void	validate_camera(char **tokens, int count, int *c_flag)
{
	double	fov;

	if (count != 4)
		error_exit("Camera: wrong number of arguments (expected 4)\n");
	if (*c_flag)
		error_exit("Error: Multiple cameras defined (only one allowed)\n");
	*c_flag = 1;
	validate_vector_format(tokens[1]);
	validate_normalized_vector(tokens[2]);
	validate_numeric_string(tokens[3]);
	fov = ft_atof(tokens[3]);
	validate_fov(fov);
	printf("Validated Camera: position=%s, orientation=%s, fov=%.1f\n", tokens[1], tokens[2], fov);
}

static void	validate_light(char **tokens, int count, int *l_flag)
{
	double	brightness;

	if (count != 3)
		error_exit("Light: wrong number of arguments (expected 3)\n");
	if (*l_flag)
		error_exit("Error: Multiple lights defined (only one allowed)\n");
	*l_flag = 1;
	validate_vector_format(tokens[1]);
	validate_numeric_string(tokens[2]);
	brightness = ft_atof(tokens[2]);
	validate_ratio(brightness);
	printf("Validated Light: position=%s, brightness=%.2f\n", tokens[1], brightness);
}

static void	validate_plane(char **tokens, int count)
{
	if (count != 4)
		error_exit("Plane: wrong number of arguments (expected 4)\n");
	validate_vector_format(tokens[1]);
	validate_normalized_vector(tokens[2]);
	validate_color_format(tokens[3]);
	printf("Validated Plane: position=%s, normal=%s, color=%s\n", tokens[1], tokens[2], tokens[3]);
}

static void	validate_sphere(char **tokens, int count)
{
	double	diameter;

	if (count != 4)
		error_exit("Sphere: wrong number of arguments (expected 4)\n");
	validate_vector_format(tokens[1]);
	validate_positive_double(tokens[2], "Sphere diameter");
	diameter = ft_atof(tokens[2]);
	validate_color_format(tokens[3]);
	printf("Validated Sphere: center=%s, diameter=%.2f, color=%s\n", tokens[1], diameter, tokens[3]);
}

static void	validate_cylinder(char **tokens, int count)
{
	double	diameter;
	double	height;

	if (count != 6)
		error_exit("Cylinder: wrong number of arguments (expected 6)\n");
	validate_vector_format(tokens[1]);
	validate_normalized_vector(tokens[2]);
	validate_positive_double(tokens[3], "Cylinder diameter");
	validate_positive_double(tokens[4], "Cylinder height");
	diameter = ft_atof(tokens[3]);
	height = ft_atof(tokens[4]);
	validate_color_format(tokens[5]);
	printf("Validated Cylinder: center=%s, axis=%s, diameter=%.2f, height=%.2f, color=%s\n", tokens[1], tokens[2], diameter, height, tokens[5]);
}

static void	process_line(char *line, int *a_flag, int *c_flag, int *l_flag)
{
	char	**tokens;

	if (!line || !*line)
		return ;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		error_exit("Error: Invalid line format\n");
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		validate_ambient(tokens, ft_strarrlen(tokens), a_flag);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		validate_camera(tokens, ft_strarrlen(tokens), c_flag);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		validate_light(tokens, ft_strarrlen(tokens), l_flag);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		validate_plane(tokens, ft_strarrlen(tokens));
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		validate_sphere(tokens, ft_strarrlen(tokens));
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		validate_cylinder(tokens, ft_strarrlen(tokens));
	else
		error_exit("Error: Unknown identifier\n");
	ft_free_split(tokens);
}

static void	process_buffer(char *buf, int bytes, int *a_flag, int *c_flag, int *l_flag)
{
	int		i;
	int		start;

	start = 0;
	i = 0;
	while (i <= bytes)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			buf[i] = '\0';
			if (buf[start] && buf[start] != '#')
				process_line(buf + start, a_flag, c_flag, l_flag);
			start = i + 1;
		}
		i++;
	}
}

static void	read_and_validate_file(int fd, int *a_flag, int *c_flag, int *l_flag)
{
	int		bytes;
	char	buf[4096 + 1];

	while ((bytes = read(fd, buf, 4096)) > 0)
	{
		buf[bytes] = '\0';
		process_buffer(buf, bytes, a_flag, c_flag, l_flag);
	}
	if (bytes < 0)
		error_exit("Error: Failed to read file\n");
}

static void	check_required_elements(int a_flag, int c_flag, int l_flag)
{
	if (!a_flag)
		error_exit("Error: Missing ambient light (A)\n");
	if (!c_flag)
		error_exit("Error: Missing camera (C)\n");
	if (!l_flag)
		error_exit("Error: Missing light (L)\n");
}

void	validate_rt_file(const char *filename)
{
	int		fd;
	int		a_flag;
	int		c_flag;
	int		l_flag;

	if (!filename || !*filename)
		error_exit("Error: Invalid filename\n");
	a_flag = 0;
	c_flag = 0;
	l_flag = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open file\n");
	read_and_validate_file(fd, &a_flag, &c_flag, &l_flag);
	close(fd);
	check_required_elements(a_flag, c_flag, l_flag);
	printf("Validation completed successfully!\n");
}