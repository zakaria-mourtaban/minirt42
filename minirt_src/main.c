/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* main.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/* TLC impromptu <TLC impromptu@student.21-school.ru> +#+  +:+       +#+        */
/* */
/* ************************************************************************** */

#include "includes/miniRT.h"

// Converts a t_color (doubles from 0.0-1.0) to a 32-bit integer color.
static int	color_to_int(t_color *color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * color->e[0]);
	g = (int)(255.999 * color->e[1]);
	b = (int)(255.999 * color->e[2]);
	return (r << 16 | g << 8 | b);
}

// Puts a pixel of a given color into the image buffer at (x, y).
static void	scene_pixel_put(t_image *img, int x, int y, int color)
{
	int	pixel_offset;

	pixel_offset = (y * img->line_bytes) + (x * (img->pixel_bits / 8));
	*(unsigned int *)(img->buffer + pixel_offset) = color;
}

// Calculates ray-sphere intersection. Returns intersection distance 't', or -1.0 on a miss.
static double	hit_sphere(t_point3 center, double radius, const t_ray *r)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_subtract(&r->orig, &center);
	a = vec3_dot(&r->dir, &r->dir);
	b = 2.0 * vec3_dot(&oc, &r->dir);
	c = vec3_dot(&oc, &oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

// Calculates the sphere's color based on the surface normal at the hit point.
static t_color	get_sphere_color(const t_ray *r, double t)
{
	t_point3	hit_point;
	t_vec3		normal;
	t_vec3		unit_normal;
	t_color		final_color;

	hit_point = ray_at(r, t);
	normal = vec3_subtract(&hit_point, &((t_vec3){{0, 0, -1}}));
	unit_normal = vec3_unit_vector(&normal);
	final_color = vec3_create(unit_normal.e[0] + 1, unit_normal.e[1] + 1,
			unit_normal.e[2] + 1);
	vec3_scale_inplace(&final_color, 0.5);
	return (final_color);
}

// Determines the color of a ray.
static t_color	ray_color(const t_ray *r)
{
	double		t;
	t_vec3		v1;
	t_vec3		v2;
	double		a;

	t = hit_sphere(vec3_create(0, 0, -1), 0.5, r);
	if (t > 0.0)
		return (get_sphere_color(r, t));
	v1 = vec3_unit_vector(&r->dir);
	a = 0.5 * (v1.e[1] + 1.0);
	v1 = vec3_create(1.0, 1.0, 1.0);
	v2 = vec3_create(0.5, 0.7, 1.0);
	vec3_scale_inplace(&v1, 1.0 - a);
	vec3_scale_inplace(&v2, a);
	return (vec3_add(&v1, &v2));
}

// Initializes camera parameters.
static void	camera_init(t_camera *cam, int width, int height)
{
	double		viewport_w;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_point3	upper_left;
	t_vec3		delta_sum;

	viewport_w = 2.0 * ((double)width / height);
	cam->center = vec3_create(0, 0, 0);
	viewport_u = vec3_create(viewport_w, 0, 0);
	viewport_v = vec3_create(0, -2.0, 0);
	cam->pixel_delta_u = vec3_divide(&viewport_u, width);
	cam->pixel_delta_v = vec3_divide(&viewport_v, height);
	upper_left = vec3_subtract(&cam->center, &((t_vec3){{0, 0, 1.0}}));
	vec3_add_inplace(&upper_left,
		&((t_vec3){{-viewport_w / 2, 1.0, 0}}));
	delta_sum = vec3_add(&cam->pixel_delta_u, &cam->pixel_delta_v);
	vec3_scale_inplace(&delta_sum, 0.5);
	cam->pixel00_loc = vec3_add(&upper_left, &delta_sum);
}

// Renders a single pixel for the given coordinates (i, j).
static void	render_pixel(t_scene *scene, int i, int j)
{
	t_ray		r;
	t_color		pixel_color;
	t_vec3		scaled_u;
	t_vec3		scaled_v;
	t_point3	pixel_center;

	scaled_u = vec3_scale(&scene->camera.pixel_delta_u, (double)i);
	scaled_v = vec3_scale(&scene->camera.pixel_delta_v, (double)j);
	pixel_center = vec3_add(&scene->camera.pixel00_loc, &scaled_u);
	vec3_add_inplace(&pixel_center, &scaled_v);
	r = ray_create(scene->camera.center,
			vec3_subtract(&pixel_center, &scene->camera.center));
	pixel_color = ray_color(&r);
	scene_pixel_put(&scene->image, i, j, color_to_int(&pixel_color));
}

// Loops through each pixel of the image and calls render_pixel.
static void	render(t_scene *scene)
{
	int			j;
	int			i;

	j = 0;
	ft_printf("Rendering...\n");
	while (j < scene->height)
	{
		i = 0;
		while (i < scene->width)
		{
			render_pixel(scene, i, j);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win,
		scene->image.img_ptr, 0, 0);
	ft_printf("Done.\n");
}

// Handles key presses; exits if ESC is pressed.
int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(scene->mlx, scene->win);
		mlx_destroy_image(scene->mlx, scene->image.img_ptr);
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
		exit(0);
	}
	return (0);
}

// Program entry point.
int	main(void)
{
	t_scene	scene;

	scene.width = 800;
	scene.height = 450;
	scene.mlx = mlx_init();
	if (!scene.mlx)
		return (1);
	scene.win = mlx_new_window(scene.mlx, scene.width, scene.height, "miniRT");
	scene.image.img_ptr = mlx_new_image(scene.mlx, scene.width, scene.height);
	scene.image.buffer = mlx_get_data_addr(scene.image.img_ptr,
			&scene.image.pixel_bits, &scene.image.line_bytes,
			&scene.image.endian);
	camera_init(&scene.camera, scene.width, scene.height);
	render(&scene);
	mlx_hook(scene.win, 2, 1L << 0, key_hook, &scene);
	mlx_loop(scene.mlx);
	return (0);
}