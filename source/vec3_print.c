/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:00:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 14:00:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vectors/vec3_print.h"
#include "../ft_printf/ft_printf.h"

void	vec3_print(const t_vec3 *v)
{
	ft_printf("%f %f %f", v->e[0], v->e[1], v->e[2]);
}
