/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:02:24 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:25:37 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../../ft_printf/ft_printf.h"
# include "../../libft/libft.h"
# include "../../minilibx/mlx.h"
# include "camera.h"
# include "color.h"
# include "hittable_list.h"
# include "interval.h"
# include "ray.h"
# include "sphere.h"
# include "structs.h"
# include "vectors/vec3.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

double	random_double(void);
double	random_double_range(double min, double max);

# define WIDTH 1920
# define HEIGHT 1080

# define KEY_ESC 65307

#endif