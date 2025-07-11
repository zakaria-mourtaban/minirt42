/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/interval.h"
#include <math.h>
#include <stdbool.h>

t_interval	interval_new(double min, double max)
{
	return ((t_interval){min, max});
}

bool	interval_contains(const t_interval *i, double x)
{
	return (i->min <= x && x <= i->max);
}

bool	interval_surrounds(const t_interval *i, double x)
{
	return (i->min < x && x < i->max);
}

double	interval_clamp(const t_interval *i, double x)
{
	if (x < i->min)
	{
		return (i->min);
	}
	if (x > i->max)
	{
		return (i->max);
	}
	return (x);
}
