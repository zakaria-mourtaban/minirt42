/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:21:56 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/24 11:37:23 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/hittable_list.h"
#include "includes/minirt.h"
#include "includes/parsing/parse_file.h"
#include "includes/validation/validate_file.h"
#include "includes/key_hooks.h"
#include "includes/handle_render.h"

static t_vec3	sample_square(void)
{
	return (vec3_create(random_double() - 0.5, random_double() - 0.5, 0));
}

t_ray	get_ray(t_camera *cam, int i, int j)
{
	t_vec3	offset;
	t_vec3	u_offset;
	t_vec3	v_offset;
	t_vec3	target;
	t_vec3	ray_direction;
	double	u_param;
	double	v_param;

	offset = sample_square();
	u_param = (i + offset.e[0]) / (cam->image_width - 1);
	v_param = (j + offset.e[1]) / (cam->image_height - 1);
	target = cam->pixel00_loc;
	u_offset = vec3_scale(&cam->horizontal, u_param);
	v_offset = vec3_scale(&cam->vertical, v_param);
	target = vec3_add(&target, &u_offset);
	target = vec3_subtract(&target, &v_offset);
	ray_direction = vec3_subtract(&target, &cam->center);
	return (ray_create(cam->center, ray_direction));
}

void	initialize_scene(t_scene *scene)
{
	int	i;

	scene->state = RENDERING;
	scene->rerender_needed = true;
	scene->last_x = -1;
	i = -1;
	while (++i < 256)
		scene->keys_pressed[i] = false;
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (1);
	scene.camera = malloc(sizeof(t_camera));
	if (!scene.camera)
		return (1);
	scene.world = hittable_list_new(8);
	(validate_rt_file(argv[1]), parse_rt_file(argv[1], &scene));
	initialize_camera(scene.camera);
	scene.rerender_needed = true;
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, scene.camera->image_width,
			scene.camera->image_height, "miniRT");
	scene.camera->image.img_ptr = mlx_new_image(
			scene.mlx, scene.camera->image_width, scene.camera->image_height);
	scene.camera->image.buffer = mlx_get_data_addr(
			scene.camera->image.img_ptr, &scene.camera->image.pixel_bits,
			&scene.camera->image.line_bytes, &scene.camera->image.endian);
	mlx_hook(scene.win, 2, 1L << 0, key_press_hook, &scene);
	mlx_hook(scene.win, 3, 1L << 1, key_release_hook, &scene);
	mlx_hook(scene.win, 17, 0, exit_program, &scene);
	mlx_loop_hook(scene.mlx, render_loop, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
