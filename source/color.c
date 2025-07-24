/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/24 11:44:31 by mkraytem         ###   ########.fr       */
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
	t_color		scaled_pixel;
	t_interval	intensity;
	int			result;
	int			channel;

	scaled_pixel = *pixel_color;
	vec3_scale_inplace(&scaled_pixel, 1.0 / samples_per_pixel);
	intensity = interval_new(0.000, 0.999);
	result = 0;
	channel = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[0])));
	result |= (channel << 16);
	channel = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[1])));
	result |= (channel << 8);
	channel = (int)(256 * interval_clamp(&intensity,
				linear_to_gamma(scaled_pixel.e[2])));
	result |= channel;
	return (result);
}
