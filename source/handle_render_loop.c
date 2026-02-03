/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   handle_render_loop.c							   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: zmourtab <zakariamourtaban@gmail.com>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/07/25 14:59:38 by zmourtab		  #+#	#+#			 */
/*   Updated: 2025/07/25 16:20:00 by zmourtab		 ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "includes/minirt.h"
#include "includes/handle_render_loop.h"
#include "includes/handle_render.h"
#include <math.h>
#include "mlx.h"

#define SENSITIVITY 0.002
#define MOVE_SPEED 0.5
#define M_PI 3.14159265358979323846

int mouse_move_hook(int x, int y, t_scene *scene)
{
	int dx;
	int dy;

	if (scene->state == INTERACTIVE)
	{
		dx = x - scene->camera->image_width / 2;
		dy = y - scene->camera->image_height / 2;
		if (dx != 0 || dy != 0)
		{
			scene->camera->yaw += dx * SENSITIVITY;
			scene->camera->pitch -= dy * SENSITIVITY;
			if (scene->camera->pitch > M_PI / 2.0 - 0.01)
				scene->camera->pitch = M_PI / 2.0 - 0.01;
			if (scene->camera->pitch < -M_PI / 2.0 + 0.01)
				scene->camera->pitch = -M_PI / 2.0 + 0.01;
			update_camera_direction(scene);
			scene->rerender_needed = true;
			mlx_mouse_move(scene->mlx, scene->win,
						   scene->camera->image_width / 2,
						   scene->camera->image_height / 2);
		}
	}
	return (0);
}

void process_input(t_scene *scene)
{
	t_vec3 move;
	t_vec3 right;
	t_vec3 forward;

	move = vec3_create_zero();
	forward = vec3_negate(&scene->camera->w);
	right = scene->camera->u;
	if (scene->keys_pressed[KEY_W])
		vec3_add_inplace(&move, &forward);
	if (scene->keys_pressed[KEY_S])
		vec3_subtract_inplace(&move, &forward);
	if (scene->keys_pressed[KEY_A])
		vec3_subtract_inplace(&move, &right);
	if (scene->keys_pressed[KEY_D])
		vec3_add_inplace(&move, &right);
	if (vec3_length_squared(&move) > 0.0)
	{
		move = vec3_unit_vector(&move);
		vec3_scale_inplace(&move, MOVE_SPEED);
		vec3_add_inplace(&scene->camera->lookfrom, &move);
		update_camera_direction(scene);
		scene->rerender_needed = true;
	}
}

void handle_interactive_state(t_scene *scene)
{
	process_input(scene);
	if (scene->rerender_needed)
	{
		mlx_mouse_hide(scene->mlx, scene->win);
		scene->camera->samples_per_pixel = 1;
		scene->camera->max_depth = 3;
		initialize_camera(scene->camera);
		render_frame_fast(scene);
		mlx_put_image_to_window(scene->mlx, scene->win,
								scene->camera->image.img_ptr, 0, 0);
		scene->rerender_needed = false;
	}
}

void handle_rendering_state(t_scene *scene)
{
	scene->camera->samples_per_pixel = 5;
	scene->camera->max_depth = 50;
	initialize_camera(scene->camera);
	render_frame(scene);
	mlx_put_image_to_window(scene->mlx, scene->win,
							scene->camera->image.img_ptr, 0, 0);
	scene->state = DONE;
}

int render_loop(void *param)
{
	t_scene *scene;

	scene = (t_scene *)param;
	if (scene->state == INTERACTIVE)
	{
		handle_interactive_state(scene);
	}
	else if (scene->state == RENDERING)
	{
		handle_rendering_state(scene);
	}
	return (0);
}
