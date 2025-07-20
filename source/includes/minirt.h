/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:15:40 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/20 20:24:39 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../../ft_printf/ft_printf.h"
# include "../../libft/libft.h"
# include <fcntl.h>
# include "../../minilibx/mlx.h"
# include "camera_init.h"
# include "camera.h"
# include "color.h"
# include "hittable_list.h"
# include "interval.h"
# include "random.h"
# include "ray.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"
# include "vectors/vec3.h"
# include "utils.h"
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include "validation/validate_file.h"
# include "../includes/validation/validation_utils.h"
# include "../includes/validation/validation_utils2.h"
# include "../includes/validation/validate_elements.h"
# include "../includes/validation/validate_elements2.h"

typedef struct s_camera	t_camera;

typedef enum e_state
{
	INTERACTIVE,
	RENDERING,
	DONE
}	t_state;

// Light struct as described in the subject
typedef struct s_light
{
	t_point3	position;
	double		brightness;
}	t_light;

typedef struct s_scene
{
	t_camera		*camera;
	t_hittable_list	*world;
	void			*mlx;
	void			*win;
	t_image			image;
	t_state			state;
	int				last_x;
	int				last_y;
	bool			rerender_needed;
	bool			keys_pressed[256];
	// Lighting information from the subject
	t_color			ambient_color;
	double			ambient_ratio;
	t_light			light;
}	t_scene;

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_R 114
#  define BUF_SIZE 4096
# else
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_R 15
# endif

#endif