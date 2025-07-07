/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:24:08 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 00:18:31 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "hittable_list.h"
# include "vectors/vec3.h"

// Forward declaration of t_camera to break the circular dependency.
typedef struct s_camera	t_camera;

// The main scene struct, holding all components of our world.
typedef struct s_scene
{
	t_camera			*camera;
	t_hittable_list		*world;
}						t_scene;

#endif