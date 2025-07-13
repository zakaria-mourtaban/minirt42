/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* main.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_name <your_email@example.com>         +#+  +:+       +#+        */
/*+#+#+#+#+#+   +#+           */
/* Created: 2025/07/08 00:22:30 by zmourtab          #+#    #+#             */
/* Updated: 2025/07/14 01:20:00 by your_name       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "includes/minirt.h"

static t_color	ray_color(const t_ray *r, t_scene *scene, int depth);
static void		render_frame(t_scene *scene);
static void		update_camera_vectors(t_scene *scene);
static int		key_press_hook(int keycode, t_scene *scene);
static int		key_release_hook(int keycode, t_scene *scene);

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

int	color_to_int(const t_color *pixel_color, int samples_per_pixel)
{
	double			scale;
	t_color			scaled_pixel;
	const t_interval	intensity = interval_new(0.000, 0.999);
	int				r;
	int				g;
	int				b;

	scaled_pixel = *pixel_color;
	scale = 1.0 / samples_per_pixel;
	vec3_scale_inplace(&scaled_pixel, scale);
	r = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[0])));
	g = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[1])));
	b = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[2])));
	return ((r << 16) | (g << 8) | b);
}

static t_color	phong_lighting(t_scene *scene, t_hit_record *rec)
{
	t_color	ambient;
	t_color	diffuse;
	t_vec3	light_dir;
	double	light_dist;
	t_ray	shadow_ray;
	double	diff;
	t_vec3	shadow_ray_orig;
	t_vec3	offset;
	t_color	light_color;
	t_color	object_color;
	t_color	ambient_contrib;
	t_color	diffuse_contrib;

	ambient = vec3_scale(&scene->ambient_color, scene->ambient_ratio);
	light_dir = vec3_subtract(&scene->light.position, &rec->p);
	light_dist = vec3_length(&light_dir);
	light_dir = vec3_unit_vector(&light_dir);
	offset = vec3_scale(&rec->normal, 1e-4);
	shadow_ray_orig = vec3_add(&rec->p, &offset);
	shadow_ray = ray_create(shadow_ray_orig, light_dir);
	if (hittable_list_hit((t_hittable *)scene->world, &shadow_ray,
		interval_new(0, light_dist), &(t_hit_record){}))
		diff = 0;
	else
		diff = fmax(vec3_dot(&rec->normal, &light_dir), 0.0);
	light_color = (t_color){{1.0, 1.0, 1.0}};
	diffuse = vec3_scale(&light_color, diff * scene->light.brightness);
	object_color = rec->mat->albedo;
	ambient_contrib = vec3_multiply_components(&object_color, &ambient);
	diffuse_contrib = vec3_multiply_components(&object_color, &diffuse);
	return (vec3_add(&ambient_contrib, &diffuse_contrib));
}

static t_color	ray_color(const t_ray *r, t_scene *scene, int depth)
{
	t_hit_record	rec;
	t_ray			scattered_ray;
	t_color			attenuation;
	t_color			scattered_color;

	if (depth <= 0)
		return (vec3_create(0, 0, 0));
	// If the ray hits nothing, return black (no sky).
	if (!hittable_list_hit((t_hittable *)scene->world, r,
		interval_new(0.001, INFINITY), &rec))
	{
		return (vec3_create(0, 0, 0));
	}
	// If the material is reflective/refractive, calculate scattered color.
	if (rec.mat->scatter(rec.mat, r, &rec, &attenuation, &scattered_ray))
	{
		scattered_color = ray_color(&scattered_ray, scene, depth - 1);
		return (vec3_multiply_components(&attenuation, &scattered_color));
	}
	// Otherwise, calculate the color from direct lighting.
	return (phong_lighting(scene, &rec));
}

static t_vec3	sample_square(void)
{
	return (vec3_create(random_double() - 0.5, random_double() - 0.5, 0));
}

t_ray	get_ray(t_camera *cam, int i, int j)
{
	t_vec3	offset;
	t_vec3	pixel_sample;
	t_vec3	scaled_u;
	t_vec3	scaled_v;
	t_vec3	ray_direction;

	offset = sample_square();
	pixel_sample = cam->pixel00_loc;
	scaled_u = vec3_scale(&cam->pixel_delta_u, i + offset.e[0]);
	scaled_v = vec3_scale(&cam->pixel_delta_v, j + offset.e[1]);
	vec3_add_inplace(&pixel_sample, &scaled_u);
	vec3_add_inplace(&pixel_sample, &scaled_v);
	ray_direction = vec3_subtract(&pixel_sample, &cam->center);
	return (ray_create(cam->center, ray_direction));
}

static t_color	render_pixel(t_camera *cam, int i, int j, t_scene *scene)
{
	t_color	pixel_color;
	t_ray	r;
	t_color	ray_c;
	int		sample;

	pixel_color = vec3_create(0, 0, 0);
	sample = 0;
	while (sample < cam->samples_per_pixel)
	{
		r = get_ray(cam, i, j);
		ray_c = ray_color(&r, scene, cam->max_depth);
		vec3_add_inplace(&pixel_color, &ray_c);
		sample++;
	}
	return (pixel_color);
}

static void	render_frame(t_scene *scene)
{
	char	*dst;
	t_color	pixel_color;
	int		i;
	int		j;

	j = 0;
	while (j < scene->camera->image_height)
	{
		ft_printf("\rScanlines remaining: %d ",
			(scene->camera->image_height - j));
		i = 0;
		while (i < scene->camera->image_width)
		{
			pixel_color = render_pixel(scene->camera, i, j, scene);
			dst = scene->camera->image.buffer + (j
					* scene->camera->image.line_bytes + i
					* (scene->camera->image.pixel_bits / 8));
			*(unsigned int *)dst = color_to_int(&pixel_color,
					scene->camera->samples_per_pixel);
			i++;
		}
		j++;
	}
	ft_printf("\rDone.                 \n");
}

int	exit_program(t_scene *scene)
{
	hittable_list_free(scene->world);
	free(scene->camera);
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	free(scene->mlx);
	exit(0);
}

static int	key_press_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
		exit_program(scene);
	if (keycode == KEY_R && scene->state == INTERACTIVE)
	{
		ft_printf("\n'R' key pressed. Starting high-quality render...\n");
		scene->state = RENDERING;
	}
	if (keycode >= 0 && keycode < 256)
		scene->keys_pressed[keycode] = true;
	return (0);
}

static int	key_release_hook(int keycode, t_scene *scene)
{
	if (keycode >= 0 && keycode < 256)
		scene->keys_pressed[keycode] = false;
	return (0);
}

int	mouse_hook(int x, int y, t_scene *scene)
{
	int		delta_x;
	int		delta_y;
	double	sensitivity;

	if (scene->state != INTERACTIVE)
		return (0);
	if (scene->last_x == -1)
	{
		scene->last_x = x;
		scene->last_y = y;
		return (0);
	}
	delta_x = x - scene->last_x;
	delta_y = y - scene->last_y;
	sensitivity = 0.003;
	scene->camera->yaw += delta_x * sensitivity;
	scene->camera->pitch -= delta_y * sensitivity;
	if (scene->camera->pitch > M_PI_2 - 0.01)
		scene->camera->pitch = M_PI_2 - 0.01;
	if (scene->camera->pitch < -M_PI_2 + 0.01)
		scene->camera->pitch = -M_PI_2 + 0.01;
	scene->rerender_needed = true;
	scene->last_x = x;
	scene->last_y = y;
	return (0);
}

static void	update_camera_vectors(t_scene *scene)
{
	double	move_speed;
	t_vec3	fwd;
	t_vec3	right;
	t_vec3	move_delta;
	t_vec3	dir;

	move_speed = 0.2;
	move_delta = vec3_create(0, 0, 0);
	fwd = vec3_create(cos(scene->camera->yaw), 0, sin(scene->camera->yaw));
	right = vec3_create(-sin(scene->camera->yaw), 0, cos(scene->camera->yaw));
	if (scene->keys_pressed[KEY_W])
		vec3_add_inplace(&move_delta, &fwd);
	if (scene->keys_pressed[KEY_S])
		vec3_subtract_inplace(&move_delta, &fwd);
	if (scene->keys_pressed[KEY_D])
		vec3_add_inplace(&move_delta, &right);
	if (scene->keys_pressed[KEY_A])
		vec3_subtract_inplace(&move_delta, &right);
	if (vec3_length_squared(&move_delta) > 0.0)
	{
		vec3_scale_inplace(&move_delta, move_speed);
		vec3_add_inplace(&scene->camera->lookfrom, &move_delta);
		scene->rerender_needed = true;
	}
	dir = (t_vec3){{cos(scene->camera->yaw) * cos(scene->camera->pitch),
		sin(scene->camera->pitch),
		sin(scene->camera->yaw) * cos(scene->camera->pitch)}};
	scene->camera->lookat = vec3_add(&scene->camera->lookfrom, &dir);
}

static int	render_loop(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (scene->state == INTERACTIVE)
	{
		update_camera_vectors(scene);
		if (scene->rerender_needed)
		{
			scene->camera->samples_per_pixel = 1;
			scene->camera->max_depth = 5;
			initialize_camera(scene->camera);
			render_frame(scene);
			mlx_put_image_to_window(scene->mlx, scene->win,
				scene->camera->image.img_ptr, 0, 0);
			scene->rerender_needed = false;
		}
	}
	else if (scene->state == RENDERING)
	{
		scene->camera->samples_per_pixel = 100;
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

static void	initialize_world(t_scene *scene)
{
	t_material	mat_ground;
	t_material	mat_ball1;
	t_material	mat_ball2;
	t_material	mat_cyl;

	scene->ambient_color = (t_color){{1.0, 1.0, 1.0}};
	scene->ambient_ratio = 0.1;
	scene->light.position = (t_point3){{-10, 10, 10}};
	scene->light.brightness = 0.8;
	mat_ground = material_new_lambertian(&(t_color){{0.5, 0.5, 0.5}});
	mat_ball1 = material_new_metal(&(t_color){{0.8, 0.1, 0.1}}, 0.1);
	mat_ball2 = material_new_metal(&(t_color){{0.8, 0.8, 0.8}}, 0.0);
	mat_cyl = material_new_metal(&(t_color){{0.8, 0.6, 0.2}}, 0.3);
	scene->world = hittable_list_new(4);
	hittable_list_add(scene->world, (t_hittable *)plane_new(
		(t_point3){{0, 0, 0}},
		(t_vec3){{0, 1, 0}},
		mat_ground));
	hittable_list_add(scene->world, (t_hittable *)sphere_new(
		(t_point3){{-1.5, 1, -1}},
		2.0,
		mat_ball1));
	hittable_list_add(scene->world, (t_hittable *)sphere_new(
		(t_point3){{1.5, 1, -1}},
		2.0,
		mat_ball2));
	hittable_list_add(scene->world, (t_hittable *)cylinder_new(
		(t_point3){{0, 2.0, -1}},
		(t_vec3){{0, 1, 0}},
		5.0,
		5.0,
		mat_cyl));
}

void	initialize_scene(t_scene *scene)
{
	t_vec3	dir;
	t_vec3	initial_dir_vec;
	int		i;

	scene->state = INTERACTIVE;
	scene->rerender_needed = true;
	scene->last_x = -1;
	i = -1;
	while (++i < 256)
		scene->keys_pressed[i] = false;
	initialize_world(scene);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		exit(1);
	scene->camera->aspect_ratio = 16.0 / 9.0;
	scene->camera->image_width = 500;
	scene->camera->image_height = fmax(1, scene->camera->image_width
			/ scene->camera->aspect_ratio);
	scene->camera->vfov = 70;
	scene->camera->lookfrom = vec3_create(0, 2, -10);
	scene->camera->lookat = vec3_create(0, 2, -1);
	scene->camera->vup = vec3_create(0, 1, 0);
	initial_dir_vec = vec3_subtract(&scene->camera->lookat,
			&scene->camera->lookfrom);
	dir = vec3_unit_vector(&initial_dir_vec);
	scene->camera->yaw = atan2(dir.e[2], dir.e[0]);
	scene->camera->pitch = asin(dir.e[1]);
}

int	main(void)
{
	t_scene	scene;

	initialize_scene(&scene);
	initialize_camera(scene.camera);
	scene.mlx = mlx_init();
	scene.win = mlx_new_window(scene.mlx, scene.camera->image_width,
			scene.camera->image_height, "miniRT");
	scene.camera->image.img_ptr = mlx_new_image(scene.mlx,
			scene.camera->image_width, scene.camera->image_height);
	scene.camera->image.buffer = mlx_get_data_addr(
			scene.camera->image.img_ptr,
			&scene.camera->image.pixel_bits,
			&scene.camera->image.line_bytes,
			&scene.camera->image.endian);
	mlx_hook(scene.win, 2, 1L << 0, key_press_hook, &scene);
	mlx_hook(scene.win, 3, 1L << 1, key_release_hook, &scene);
	mlx_hook(scene.win, 6, 1L << 6, mouse_hook, &scene);
	mlx_hook(scene.win, 17, 0, exit_program, &scene);
	mlx_loop_hook(scene.mlx, render_loop, &scene);
	mlx_loop(scene.mlx);
	return (0);
}