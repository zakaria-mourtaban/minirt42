/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:13:50 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/07 17:13:51 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "../../ft_printf/ft_printf.h"
# include "vectors/vec3.h"

typedef t_vec3		t_color;

static inline void	write_color(const t_color *pixel_color)
{
	int	rbyte;
	int	gbyte;
	int	bbyte;

	rbyte = (int)(255.999 * pixel_color->e[0]);
	gbyte = (int)(255.999 * pixel_color->e[1]);
	bbyte = (int)(255.999 * pixel_color->e[2]);
	ft_printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif