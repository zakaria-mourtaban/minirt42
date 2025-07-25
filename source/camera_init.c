/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:30:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/14 00:26:30 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static void	init_viewport(t_camera *camera, double viewport_height,
		double viewport_width)
{
	t_vec3		viewport_u;
	t_vec3		viewport_v;

	viewport_u = vec3_scale(&camera->u, viewport_width);
	viewport_v = vec3_scale(&camera->v, -viewport_height);
	camera->pixel_delta_u = vec3_divide(&viewport_u, camera->image_width);
	camera->pixel_delta_v = vec3_divide(&viewport_v, camera->image_height);
}

static void	init_camera_vectors(t_camera *camera)
{
	t_vec3		temp_vec;

	temp_vec = vec3_subtract(&camera->lookfrom, &camera->lookat);
	camera->w = vec3_unit(temp_vec);
	temp_vec = vec3_cross(&camera->vup, &camera->w);
	camera->u = vec3_unit(temp_vec);
	camera->v = vec3_cross(&camera->w, &camera->u);
}

static void	init_upper_left(t_camera *camera)
{
    t_vec3 half_horizontal;
    t_vec3 half_vertical;

    // Formula: origin - (horizontal/2) + (vertical/2) - w
    half_horizontal = vec3_divide(&camera->horizontal, 2.0);
    half_vertical = vec3_divide(&camera->vertical, 2.0);

    camera->pixel00_loc = vec3_subtract(&camera->lookfrom, &half_horizontal);
    camera->pixel00_loc = vec3_add(&camera->pixel00_loc, &half_vertical);
    camera->pixel00_loc = vec3_subtract(&camera->pixel00_loc, &camera->w);
}

void	initialize_camera(t_camera *camera)
{
	double		focal_length;
	double		viewport_height;
	double		viewport_width;
	t_vec3		look_dir;

	camera->image_height = camera->image_width / camera->aspect_ratio;
	if (camera->image_height < 1)
		camera->image_height = 1;
	camera->center = camera->lookfrom;
	look_dir = vec3_subtract(&camera->lookfrom, &camera->lookat);
	focal_length = vec3_length(&look_dir);
	viewport_height = 2.0 * tan(degrees_to_radians(camera->vfov) / 2.0)
		* focal_length;
	viewport_width = viewport_height * ((double)camera->image_width
			/ camera->image_height);
	init_camera_vectors(camera);
	camera->horizontal = vec3_scale(&camera->u, viewport_width);
	camera->vertical = vec3_scale(&camera->v, viewport_height);
	init_viewport(camera, viewport_height, viewport_width);
	init_upper_left(camera);
}
