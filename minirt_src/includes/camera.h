/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:03:34 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:51:27 by zmourtab         ###   ########.fr       */
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
} t_image;

// Manages rendering parameters and the main render loop.
typedef struct s_camera
{
	// Public parameters
	double		aspect_ratio;
	int			image_width;
	int			samples_per_pixel;

	// Private state
	int			image_height;
	double		pixel_samples_scale;
	t_point3	center;
	t_point3	pixel00_loc;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;

	// Back-buffer for rendering
	void		*mlx;
	void		*win;
	t_image		image;
} t_camera;

void			camera_render(t_camera *cam, t_hittable_list *world);
t_ray			get_ray(t_camera *cam, int i, int j);

#endif