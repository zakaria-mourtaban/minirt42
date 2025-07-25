/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkraytem <mkraytem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:51:16 by mkraytem          #+#    #+#             */
/*   Updated: 2025/07/24 10:52:07 by mkraytem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HOOKS_H
# define KEY_HOOKS_H

# include "minirt.h"

int	exit_program(t_scene *scene);
int	key_press_hook(int keycode, t_scene *scene);
int	key_release_hook(int keycode, t_scene *scene);

#endif 