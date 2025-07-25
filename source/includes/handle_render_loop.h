/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_render_loop.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:50:24 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/25 16:54:13 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_RENDER_LOOP_H
# define HANDLE_RENDER_LOOP_H

# include "minirt.h"

t_color		render_pixel(t_camera *cam, int i, int j, t_scene *scene);
void		render_frame(t_scene *scene);
int			render_loop(void *param);
int			mouse_move_hook(int x, int y, t_scene *scene);
void		update_camera_direction(t_scene *scene);

#endif