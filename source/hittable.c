/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 00:44:18 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/11 12:25:48 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/hittable.h"
#include "./includes/ray.h" // Include the full ray definition here

void	set_face_normal(t_hit_record *rec, const t_ray *r,
		const t_vec3 *outward_normal)
{
	rec->front_face = vec3_dot(&r->dir, outward_normal) < 0;
	if (rec->front_face)
	{
		rec->normal = *outward_normal;
	}
	else
	{
		rec->normal = vec3_negate(outward_normal);
	}
}
