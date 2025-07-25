/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42student <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 00:00:00 by 42student         #+#    #+#             */
/*   Updated: 2024/07/14 00:00:00 by 42student        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include "../minirt.h"
# include "./parse_ambient.h"
# include "./parse_camera.h"
# include "./parse_cylinder.h"
# include "./parse_sphere.h"
# include "./parse_light.h"
# include "./parse_plane.h"

void	dispatch_element(char **tokens, t_scene *scene);
void	parse_rt_file(const char *filename, t_scene *scene);

#endif 