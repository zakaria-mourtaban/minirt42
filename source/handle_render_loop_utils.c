/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render_loop_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:52:35 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/25 16:54:17 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/handle_render_loop.h"
#include <math.h>
#include "mlx.h"

void	update_camera_direction(t_scene *scene)
{
	t_vec3	direction;

	direction.e[0] = cos(scene->camera->yaw) * cos(scene->camera->pitch);
	direction.e[1] = sin(scene->camera->pitch);
	direction.e[2] = sin(scene->camera->yaw) * cos(scene->camera->pitch);
	scene->camera->lookat = vec3_add(&scene->camera->lookfrom, &direction);
}
