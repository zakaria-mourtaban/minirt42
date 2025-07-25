/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:17:44 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/25 14:00:38 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static t_color	background_color(const t_ray *r)
{
	t_vec3		unit_dir;
	double		a;
	t_color		start;
	t_color		end;

	unit_dir = vec3_unit_vector(&r->dir);
	a = 0.5 * (unit_dir.e[1] + 1.0);
	start = vec3_create(1.0, 1.0, 1.0);
	end = vec3_create(0.5, 0.7, 1.0);
	vec3_scale_inplace(&start, 1.0 - a);
	vec3_scale_inplace(&end, a);
	return (vec3_add(&start, &end));
}

static t_color	ray_color(const t_ray *r, t_scene *scene, int depth)
{
	t_hit_record		rec;
	t_scatter_record	srec;
	t_color				scattered;

	if (depth <= 0)
		return (vec3_create(0, 0, 0));
	if (!hittable_list_hit((t_hittable *)scene->world, r,
			interval_new(0.001, INFINITY), &rec))
		return (background_color(r));
	if (rec.mat->scatter(rec.mat, r, &rec, &srec))
	{
		scattered = ray_color(&srec.scattered, scene, depth - 1);
		return (vec3_multiply_components(&srec.attenuation, &scattered));
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
	if (scene->state != DONE)
	{
		scene = (t_scene *)param;
		scene->camera->samples_per_pixel = 1;
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
