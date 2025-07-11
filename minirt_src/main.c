/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:22:30 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 10:26:48 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

static t_color	ray_color(const t_ray *r, t_hittable_list *world, int depth);
void	initialize_camera(t_camera *camera);

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

int	color_to_int(const t_color *pixel_color, int samples_per_pixel)
{
	double				r;
	double				g;
	double				b;
	double				scale;
	t_color				scaled_pixel;
	const t_interval	intensity = interval_new(0.000, 0.999);
	int					r_int;
	int					g_int;
	int					b_int;

	scaled_pixel = *pixel_color;
	scale = 1.0 / samples_per_pixel;
	vec3_scale_inplace(&scaled_pixel, scale);
	r = scaled_pixel.e[0];
	g = scaled_pixel.e[1];
	b = scaled_pixel.e[2];
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);
	r_int = (int)(256 * interval_clamp(&intensity, r));
	g_int = (int)(256 * interval_clamp(&intensity, g));
	b_int = (int)(256 * interval_clamp(&intensity, b));
	return ((r_int << 16) | (g_int << 8) | b_int);
}

static t_color	ray_color_scattered(const t_ray *r, t_hittable_list *world,
		int depth, t_hit_record *rec)
{
	t_color	scattered_color;
	t_ray	scattered;
	t_color	attenuation;

	if (rec->mat->scatter(rec->mat, r, rec, &attenuation, &scattered))
	{
		scattered_color = ray_color(&scattered, world, depth - 1);
		return (vec3_multiply_components(&attenuation, &scattered_color));
	}
	return (vec3_create(0, 0, 0));
}

static t_color	ray_color_background(const t_ray *r)
{
	t_vec3	unit_dir;
	double	a;
	t_vec3	start_color;
	t_vec3	end_color;

	unit_dir = vec3_unit_vector(&r->dir);
	a = 0.5 * (unit_dir.e[1] + 1.0);
	start_color = vec3_create(1.0, 1.0, 1.0);
	vec3_scale_inplace(&start_color, 1.0 - a);
	end_color = vec3_create(0.5, 0.7, 1.0);
	vec3_scale_inplace(&end_color, a);
	return (vec3_add(&start_color, &end_color));
}

static t_color	ray_color(const t_ray *r, t_hittable_list *world, int depth)
{
	t_hit_record	rec;

	if (depth <= 0)
		return (vec3_create(0, 0, 0));
	if (hittable_list_hit((t_hittable *)world, r, interval_new(0.001, INFINITY),
			&rec))
	{
		return (ray_color_scattered(r, world, depth, &rec));
	}
	return (ray_color_background(r));
}

static t_vec3	sample_square(void)
{
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

void	initialize_camera(t_camera *camera)
{
	double		h;
	double		theta;
	double		focal_length;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	double		viewport_height;
	double		viewport_width;
	t_point3	viewport_upper_left;
	t_vec3		temp_vec;
	t_vec3		temp_vec2;
	t_vec3		temp_vec3;

	camera->image_height = camera->image_width / camera->aspect_ratio;
	if (camera->image_height < 1)
		camera->image_height = 1;
	camera->center = camera->lookfrom;
	temp_vec = vec3_subtract(&camera->lookfrom, &camera->lookat);
	focal_length = vec3_length(&temp_vec);
	theta = degrees_to_radians(camera->vfov);
	h = tan(theta / 2.0);
	viewport_height = 2.0 * h * focal_length;
	viewport_width = viewport_height * ((double)camera->image_width
			/ camera->image_height);
	temp_vec = vec3_subtract(&camera->lookfrom, &camera->lookat);
	camera->w = vec3_unit(temp_vec);
	temp_vec = vec3_cross(&camera->vup, &camera->w);
	camera->u = vec3_unit(temp_vec);
	camera->v = vec3_cross(&camera->w, &camera->u);
	viewport_u = vec3_scale(&camera->u, viewport_width);
	viewport_v = vec3_scale(&camera->v, -viewport_height);
	camera->pixel_delta_u = vec3_divide(&viewport_u, camera->image_width);
	camera->pixel_delta_v = vec3_divide(&viewport_v, camera->image_height);
	temp_vec = vec3_scale(&camera->w, focal_length);
	viewport_upper_left = vec3_subtract(&camera->center, &temp_vec);
	temp_vec2 = vec3_divide(&viewport_u, 2);
	viewport_upper_left = vec3_subtract(&viewport_upper_left, &temp_vec2);
	temp_vec3 = vec3_divide(&viewport_v, 2);
	viewport_upper_left = vec3_subtract(&viewport_upper_left, &temp_vec3);
	temp_vec = vec3_add(&camera->pixel_delta_u, &camera->pixel_delta_v);
	temp_vec2 = vec3_scale(&temp_vec, 0.5);
	camera->pixel00_loc = vec3_add(&viewport_upper_left, &temp_vec2);
}

static t_color	render_pixel(t_camera *cam, int i, int j,
		t_hittable_list *world, int max_depth)
{
	t_color	pixel_color;
	t_ray	r;
	t_color	sampled_color;
	int		sample;

	pixel_color = vec3_create(0, 0, 0);
	sample = 0;
	while (sample < cam->samples_per_pixel)
	{
		r = get_ray(cam, i, j);
		sampled_color = ray_color(&r, world, max_depth);
		vec3_add_inplace(&pixel_color, &sampled_color);
		sample++;
	}
	return (pixel_color);
}

static void	render_scanline(t_camera *cam, int j, t_hittable_list *world,
		int max_depth)
{
	char	*dst;
	t_color	pixel_color;
	int		i;

	ft_printf("\rScanlines remaining: %d ", (cam->image_height - j));
	i = 0;
	while (i < cam->image_width)
	{
		pixel_color = render_pixel(cam, i, j, world, max_depth);
		dst = cam->image.buffer + (j * cam->image.line_bytes + i
				* (cam->image.pixel_bits / 8));
		*(unsigned int *)dst = color_to_int(&pixel_color,
				cam->samples_per_pixel);
		i++;
	}
}

void	camera_render(t_camera *cam, t_hittable_list *world)
{
	const int	max_depth = 50;
	int			j;

	initialize_camera(cam);
	cam->mlx = mlx_init();
	cam->win = mlx_new_window(cam->mlx, cam->image_width, cam->image_height,
			"miniRT");
	cam->image.img_ptr = mlx_new_image(cam->mlx, cam->image_width,
			cam->image_height);
	cam->image.buffer = mlx_get_data_addr(cam->image.img_ptr,
			&cam->image.pixel_bits, &cam->image.line_bytes, &cam->image.endian);
	ft_printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
	j = 0;
	while (j < cam->image_height)
	{
		render_scanline(cam, j, world, max_depth);
		j++;
	}
	mlx_put_image_to_window(cam->mlx, cam->win, cam->image.img_ptr, 0, 0);
	mlx_loop(cam->mlx);
	ft_printf("\rDone.                 \n");
}

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

static void	initialize_world(t_hittable_list **world)
{
	t_material	material_ground;
	t_material	material_center;
	t_material	material_left;
	t_material	material_right;

	*world = hittable_list_new(4);
	material_ground = material_new_lambertian(&(t_color){{0.8, 0.8, 0.0}});
	material_center = material_new_lambertian(&(t_color){{0.1, 0.2, 0.5}});
	material_left = material_new_metal(&(t_color){{0.8, 0.8, 0.8}}, 0.3);
	material_right = material_new_metal(&(t_color){{0.8, 0.6, 0.2}}, 1.0);
	hittable_list_add(*world, (t_hittable *)sphere_new((t_point3){{0.0, -100.5,
			-1.0}}, 100.0, material_ground));
	hittable_list_add(*world, (t_hittable *)sphere_new((t_point3){{0.0, 0.0,
			-1.0}}, 0.5, material_center));
	hittable_list_add(*world, (t_hittable *)sphere_new((t_point3){{-1.0, 0.0,
			-1.0}}, 0.5, material_left));
	hittable_list_add(*world, (t_hittable *)sphere_new((t_point3){{1.0, 0.0,
			-1.0}}, 0.5, material_right));
}

int	main(void)
{
	t_hittable_list	*world;
	t_camera		cam;

	initialize_world(&world);
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 800;
	cam.samples_per_pixel = 100;
	cam.vfov = 90;
	cam.lookfrom = vec3_create(-2, 2, 1);
	cam.lookat = vec3_create(0, 0, -1);
	cam.vup = vec3_create(0, 1, 0);
	camera_render(&cam, world);
	hittable_list_free(world);
	return (0);
}
