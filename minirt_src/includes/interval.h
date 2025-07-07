/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:57:53 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:20:44 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include <math.h>
# include <stdbool.h>

/**
 * @struct t_interval
 * @brief Represents a real-valued interval with a minimum and maximum.
 */
typedef struct s_interval
{
	double					min;
	double					max;
}							t_interval;

// Global constant intervals
static const t_interval		g_empty_interval = {+INFINITY, -INFINITY};
static const t_interval		g_universe_interval = {-INFINITY, +INFINITY};

// Functions for creating and working with intervals
static inline t_interval	interval_new(double min, double max)
{
	return ((t_interval){min, max});
}

static inline bool	interval_contains(const t_interval *i, double x)
{
	return (i->min <= x && x <= i->max);
}

static inline bool	interval_surrounds(const t_interval *i, double x)
{
	return (i->min < x && x < i->max);
}

static inline double	interval_clamp(const t_interval *i, double x)
{
	if (x < i->min)
		return (i->min);
	if (x > i->max)
		return (i->max);
	return (x);
}

#endif