/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:22:30 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:26:34 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

static int	color_to_int(t_color *color, int samples_per_pixel)
{
	double					r;
	double					g;
	double					b;
	double					scale;
	static const t_interval	intensity = {0.000, 0.999};

	r = color->e[0];
	g = color->e[1];
	b = color->e[2];
	scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;
	return (((int)(256 * interval_clamp(&intensity, r))) << 16 | ((int)(256
				* interval_clamp(&intensity, g))) << 8 | ((int)(256
				* interval_clamp(&intensity, b))));
}

static t_color	ray_color(const t_ray *r, t_hittable_list *world)
{
	t_hit_record	rec;
	t_color			final_color;
	t_vec3			unit_dir;
	double			a;
	t_vec3			start_color;
	t_vec3			end_color;

	if (hittable_list_hit((t_hittable *)world, r, interval_new(0.001, INFINITY),
			&rec))
	{
		final_color = vec3_add(&rec.normal, &((t_vec3){{1, 1, 1}}));
		vec3_scale_inplace(&final_color, 0.5);
		return (final_color);
	}
	unit_dir = vec3_unit_vector(&r->dir);
	a = 0.5 * (unit_dir.e[1] + 1.0);
	start_color = vec3_create(1.0, 1.0, 1.0);
	vec3_scale_inplace(&start_color, 1.0 - a);
	end_color = vec3_create(0.5, 0.7, 1.0);
	vec3_scale_inplace(&end_color, a);
	final_color = vec3_add(&start_color, &end_color);
	return (final_color);
}

static t_vec3	sample_square(void)
{
	// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
	return (vec3_create(random_double() - 0.5, random_double() - 0.5, 0));
}
t_ray	get_ray(t_camera *cam, int i, int j)
{
	t_vec3		offset;
	t_vec3		pixel_sample;
	t_vec3		scaled_delta_u;
	t_vec3		scaled_delta_v;
	t_point3	ray_origin;
	t_vec3		ray_direction;

	// Construct a camera ray originating from the origin and directed at randomly sampled
	// point around the pixel location i, j.
	offset = sample_square();
	pixel_sample = cam->pixel00_loc;
	scaled_delta_u = vec3_scale(&cam->pixel_delta_u, i + offset.e[0]);
	scaled_delta_v = vec3_scale(&cam->pixel_delta_v, j + offset.e[1]);
	vec3_add_inplace(&pixel_sample, &scaled_delta_u);
	vec3_add_inplace(&pixel_sample, &scaled_delta_v);
	ray_origin = cam->center;
	ray_direction = vec3_subtract(&pixel_sample, &ray_origin);
	return (ray_create(ray_origin, ray_direction));
}

static void	camera_initialize(t_camera *cam)
{
	double	focal_length;
	double	viewport_height;
	double	viewport_width;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	viewport_upper_left;
	t_vec3	half_u;
	t_vec3	half_v;

	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel;
	cam->center = vec3_create(0, 0, 0);
	focal_length = 1.0;
	viewport_height = 2.0;
	viewport_width = viewport_height * ((double)cam->image_width
			/ cam->image_height);
	viewport_u = vec3_create(viewport_width, 0, 0);
	viewport_v = vec3_create(0, -viewport_height, 0);
	cam->pixel_delta_u = vec3_divide(&viewport_u, cam->image_width);
	cam->pixel_delta_v = vec3_divide(&viewport_v, cam->image_height);
	viewport_upper_left = vec3_subtract(&cam->center, &((t_vec3){{0, 0,
				focal_length}}));
	half_u = vec3_divide(&viewport_u, 2.0);
	half_v = vec3_divide(&viewport_v, 2.0);
	vec3_subtract_inplace(&viewport_upper_left, &half_u);
	vec3_subtract_inplace(&viewport_upper_left, &half_v);
	cam->pixel00_loc = viewport_upper_left;
}

void	camera_render(t_camera *cam, t_hittable_list *world)
{
	char	*dst;
	t_color	pixel_color;
	t_ray	r;
	t_color	sampled_color;

	camera_initialize(cam);
	cam->mlx = mlx_init();
	cam->win = mlx_new_window(cam->mlx, cam->image_width, cam->image_height,
			"miniRT");
	cam->image.img_ptr = mlx_new_image(cam->mlx, cam->image_width,
			cam->image_height);
	cam->image.buffer = mlx_get_data_addr(cam->image.img_ptr,
			&cam->image.pixel_bits, &cam->image.line_bytes, &cam->image.endian);
	ft_printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
	for (int j = 0; j < cam->image_height; ++j)
	{
		ft_printf("\rScanlines remaining: %d ", (cam->image_height - j));
		for (int i = 0; i < cam->image_width; ++i)
		{
			pixel_color = vec3_create(0, 0, 0);
			for (int sample = 0; sample < cam->samples_per_pixel; ++sample)
			{
				r = get_ray(cam, i, j);
				sampled_color = ray_color(&r, world);
				vec3_add_inplace(&pixel_color, &sampled_color);
			}
			dst = cam->image.buffer + (j * cam->image.line_bytes + i
					* (cam->image.pixel_bits / 8));
			*(unsigned int *)dst = color_to_int(&pixel_color,
					cam->samples_per_pixel);
		}
	}
	mlx_put_image_to_window(cam->mlx, cam->win, cam->image.img_ptr, 0, 0);
	ft_printf("\rDone.                 \n");
}

// --- Main Program and Hooks ---

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
	{
		hittable_list_free(scene->world);
		mlx_destroy_window(scene->camera->mlx, scene->camera->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_scene	scene;

	scene.camera = (t_camera *)malloc(sizeof(t_camera));
	// World
	scene.world = hittable_list_new(2);
	hittable_list_add(scene.world, (t_hittable *)sphere_new(vec3_create(0, 0,
				-1), 0.5));
	hittable_list_add(scene.world, (t_hittable *)sphere_new(vec3_create(0,
				-100.5, -1), 100));
	// Camera
	scene.camera->aspect_ratio = 16.0 / 9.0;
	scene.camera->image_width = 1920;
	scene.camera->samples_per_pixel = 100;
	// Render
	camera_render(scene.camera, scene.world);
	// Hooks
	mlx_hook(scene.camera->win, 2, 1L << 0, key_hook, &scene);
	mlx_loop(scene.camera->mlx);
	return (0);
}

// Hittable list implementation...
bool	hittable_list_hit(const t_hittable *self, const t_ray *r,
		t_interval ray_t, t_hit_record *rec)
{
	t_hittable_list	*list;
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	int				i;

	list = (t_hittable_list *)self;
	hit_anything = false;
	closest_so_far = ray_t.max;
	i = 0;
	while (i < list->size)
	{
		if (list->objects[i]->hit(list->objects[i], r, interval_new(ray_t.min,
					closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

t_hittable_list	*hittable_list_new(int capacity)
{
	t_hittable_list	*list;

	list = (t_hittable_list *)malloc(sizeof(t_hittable_list));
	if (!list)
		return (NULL);
	list->objects = (t_hittable **)malloc(sizeof(t_hittable *) * capacity);
	if (!list->objects)
	{
		free(list);
		return (NULL);
	}
	list->size = 0;
	list->capacity = capacity;
	list->hittable.hit = hittable_list_hit;
	return (list);
}

void	hittable_list_add(t_hittable_list *list, t_hittable *object)
{
	if (list->size < list->capacity)
		list->objects[list->size++] = object;
}

void	hittable_list_clear(t_hittable_list *list)
{
	int	i;

	i = 0;
	while (i < list->size)
		free(list->objects[i++]);
	list->size = 0;
}

void	hittable_list_free(t_hittable_list *list)
{
	hittable_list_clear(list);
	free(list->objects);
	free(list);
}