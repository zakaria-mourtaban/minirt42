/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/color.h"
#include "includes/interval.h"
#include "includes/vectors/vec3.h"
#include "../ft_printf/ft_printf.h"

void	write_color(const t_color *pixel_color, int samples_per_pixel)
{
	double		r;
	double		g;
	double		b;
	double		scale;
	const t_interval	intensity = {0.000, 0.999};

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
