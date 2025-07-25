/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:59:38 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/25 15:36:33 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/handle_render.h"

int	render_loop(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (scene->state == INTERACTIVE)
	{
		scene->camera->samples_per_pixel = 1;
		scene->camera->max_depth = 10;
		initialize_camera(scene->camera);
		render_frame(scene);
		mlx_put_image_to_window(scene->mlx, scene->win,
			scene->camera->image.img_ptr, 0, 0);
	}
	else if (scene->state == RENDERING)
	{
		ft_printf("Starting high-quality render with 500 rays per pixel...\n");
		scene->camera->samples_per_pixel = 500;
		scene->camera->max_depth = 50;
		initialize_camera(scene->camera);
		render_frame(scene);
		mlx_put_image_to_window(scene->mlx, scene->win,
			scene->camera->image.img_ptr, 0, 0);
		scene->state = DONE;
		ft_printf("High-quality render complete! Press ESC to exit.\n");
	}
	return (0);
}
