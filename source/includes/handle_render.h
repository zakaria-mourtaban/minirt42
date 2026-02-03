/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:50:24 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/24 10:52:18 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_RENDER_H
#define HANDLE_RENDER_H

#include "minirt.h"

t_color render_pixel(t_camera *cam, int i, int j, t_scene *scene);
void render_frame(t_scene *scene);
void render_frame_fast(t_scene *scene);
int render_loop(void *param);

#endif