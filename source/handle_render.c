/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:17:44 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/24 11:29:10 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static t_color	phong_lighting(t_scene *scene, t_hit_record *rec)
{
	t_color	ambient;
	t_color	diffuse;
	t_vec3	light_dir;
	double	light_dist;
	t_ray	shadow_ray;
	double	diff;
	t_vec3	offset;
	t_color	light_color;
	t_color	object_color;
	t_color	ambient_contrib;
	t_color	diffuse_contrib;
	t_vec3	shadow_ray_orig;

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
	t_hit_record		rec;
	t_scatter_record	srec;
	t_color				scattered_color;
	t_vec3				unit_dir;
	double				a;
	t_color				start_color;
	t_color				end_color;

	if (depth <= 0)
		return (vec3_create(0, 0, 0));
	if (!hittable_list_hit((t_hittable *)scene->world, r,
			interval_new(0.001, INFINITY), &rec))
	{
		unit_dir = vec3_unit_vector(&r->dir);
		a = 0.5 * (unit_dir.e[1] + 1.0);
		start_color = vec3_create(1.0, 1.0, 1.0);
		end_color = vec3_create(0.5, 0.7, 1.0);
		vec3_scale_inplace(&start_color, 1.0 - a);
		vec3_scale_inplace(&end_color, a);
		return (vec3_add(&start_color, &end_color));
	}
	if (rec.mat->scatter(rec.mat, r, &rec, &srec))
	{
		scattered_color = ray_color(&srec.scattered, scene, depth - 1);
		return (vec3_multiply_components(&srec.attenuation, &scattered_color));
	}
	return (phong_lighting(scene, &rec));
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

void	render_frame(t_scene *scene)
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
			dst = scene->camera->image.buffer
				+ (j * scene->camera->image.line_bytes
					+ i * (scene->camera->image.pixel_bits / 8));
			*(unsigned int *)dst = color_to_int(&pixel_color,
					scene->camera->samples_per_pixel);
			i++;
		}
		j++;
	}
	ft_printf("\rDone.                 \n");
}

int	render_loop(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (scene->state == INTERACTIVE)
	{
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
