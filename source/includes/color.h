/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:20:59 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/24 08:48:48 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "../../ft_printf/ft_printf.h"
# include "interval.h"
# include "vectors/vec3.h"

typedef t_vec3	t_color;

void			write_color(const t_color *pixel_color, int samples_per_pixel);
int				color_to_int(const t_color *pixel_color, int samples_per_pixel);

#endif