/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:24:08 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/06 00:58:45 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "vectors/vec3.h"

// Holds all camera parameters needed for ray generation.
typedef struct s_camera
{
	t_point3	center;
	t_point3	pixel00_loc;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
}				t_camera;

// Holds the MiniLibX image pointer and buffer details.
typedef struct s_image
{
	void		*img_ptr;
	char		*buffer;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
}				t_image;

// The main scene struct, holding all components of our world.
typedef struct s_scene
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_camera	camera;
	t_image		image;
}				t_scene;

#endif