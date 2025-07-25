/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2025/07/25 12:03:13 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

static void	process_buffer(char *buf, int bytes,
		t_element_flags *flags)
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
				process_line(buf + start, &flags->a_flag,
					&flags->c_flag, &flags->l_flag);
			start = i + 1;
		}
		i++;
	}
}

static void	read_and_validate_file(int fd, t_element_flags *flags)
{
	int		bytes;
	char	buf[4096 + 1];

	bytes = read(fd, buf, 4096);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		process_buffer(buf, bytes, flags);
		bytes = read(fd, buf, 4096);
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
	int				fd;
	t_element_flags	flags;

	if (!filename || !*filename)
		error_exit("Error: Invalid filename\n");
	flags.a_flag = 0;
	flags.c_flag = 0;
	flags.l_flag = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open file\n");
	read_and_validate_file(fd, &flags);
	close(fd);
	check_required_elements(flags.a_flag,
		flags.c_flag, flags.l_flag);
	printf("Validation completed successfully!\n");
}
