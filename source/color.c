/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/24 11:05:38 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "includes/color.h"
#include "includes/interval.h"

void	write_color(const t_color *pixel_color, int samples_per_pixel)
{
	double				r;
	double				g;
	double				b;
	double				scale;
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

static double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrt(linear_component));
	return (0);
}

int	color_to_int(const t_color *pixel_color, int samples_per_pixel)
{
	double		scale;
	t_color		scaled_pixel;
	t_interval	intensity;
	int			r;
	int			g;
	int			b;

	intensity = interval_new(0.000, 0.999);
	scaled_pixel = *pixel_color;
	scale = 1.0 / samples_per_pixel;
	vec3_scale_inplace(&scaled_pixel, scale);
	r = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[0])));
	g = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[1])));
	b = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[2])));
	return ((r << 16) | (g << 8) | b);
}
