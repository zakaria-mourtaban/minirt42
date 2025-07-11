/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:00:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 13:32:56 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../../ft_printf/ft_printf.h"
# include "../../libft/libft.h"
# include "../../minilibx/mlx.h"
# include "camera_init.h"
# include "camera.h"
# include "color.h"
# include "hittable_list.h"
# include "interval.h"
# include "random.h"
# include "ray.h"
# include "sphere.h"
# include "vectors/vec3.h"
# include "utils.h"
# include <math.h>
# include <stdlib.h>

typedef struct s_camera	t_camera;

typedef struct s_scene
{
	t_camera			*camera;
	t_hittable_list		*world;
}	t_scene;

# define KEY_ESC 65307

#endif