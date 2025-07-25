/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:53:31 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/25 14:12:18 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_LIGHTING_H
# define PHONG_LIGHTING_H

typedef struct s_scene	t_scene;

t_color	phong_lighting(t_scene *scene, t_hit_record *rec);

#endif