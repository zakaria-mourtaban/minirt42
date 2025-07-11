/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:57:53 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 13:39:27 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include <math.h>
# include <stdbool.h>

// Represents a real-valued interval with a minimum and maximum.
typedef struct s_interval
{
	double				min;
	double				max;
}						t_interval;

// Global constant intervals
static const t_interval	g_empty_interval = {+INFINITY, -INFINITY};
static const t_interval	g_universe_interval = {-INFINITY, +INFINITY};

// Functions for creating and working with intervals
t_interval				interval_new(double min, double max);
bool					interval_contains(const t_interval *i, double x);
bool					interval_surrounds(const t_interval *i, double x);
double					interval_clamp(const t_interval *i, double x);

#endif