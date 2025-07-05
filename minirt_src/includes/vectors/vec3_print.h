/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_print.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:46:31 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/05 23:53:42 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3_defs.h"
#include "../../ft_printf/ft_printf.h"

static void	print_char(char c)
{
	write(1, &c, 1);
}

/**
 * @brief Prints the vector components `x y z` to standard output.
 * This implementation uses the write() system call exclusively for output,
 * manually converting numbers to strings.
 */
static inline void	vec3_print(const t_vec3 *v)
{
	ft_printf("%f %f %f", v->e[0], v->e[1], v->e[2]);
}
