/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:20:59 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:21:32 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "../../ft_printf/ft_printf.h"
# include "interval.h"
# include "vectors/vec3.h"

typedef t_vec3		t_color;

static inline void	write_color(const t_color *pixel_color,
		int samples_per_pixel)
{
	double					r;
	double					g;
	double					b;
	double					scale;
	static const t_interval	intensity = {0.000, 0.999};

	r = pixel_color->e[0];
	g = pixel_color->e[1];
	b = pixel_color->e[2];
	scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;
	ft_printf("%d %d %d\n", (int)(256 * interval_clamp(&intensity, r)),
		(int)(256 * interval_clamp(&intensity, g)), (int)(256
			* interval_clamp(&intensity, b)));
}

#endif