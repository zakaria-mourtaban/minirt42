/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:03:34 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 10:16:04 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "hittable.h"
# include "hittable_list.h"
# include "ray.h"

// Holds the image buffer and its properties.
typedef struct s_image
{
	void		*img_ptr;
	char		*buffer;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
}	t_image;

typedef struct s_camera
{
	double		aspect_ratio;
	int			image_width;
	double		vfov;
	t_vec3		lookfrom;
	t_vec3		lookat;
	t_vec3		vup;
	int			samples_per_pixel;
	int			max_depth;

	int			image_height;
	t_vec3		center;
	t_vec3		pixel00_loc;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;

	void		*mlx;
	void		*win;
	t_image		image;
}	t_camera;

void			camera_render(t_camera *cam, t_hittable_list *world);
t_ray			get_ray(t_camera *cam, int i, int j);

#endif