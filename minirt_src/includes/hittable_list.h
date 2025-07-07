/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 23:43:07 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/07 23:58:29 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "hittable.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_hittable_list
{
	t_hittable	hittable;
	t_hittable	**objects;
	int			size;
	int			capacity;
}				t_hittable_list;

// Function prototypes
t_hittable_list	*hittable_list_new(int capacity);
void			hittable_list_add(t_hittable_list *list, t_hittable *object);
void			hittable_list_clear(t_hittable_list *list);
void			hittable_list_free(t_hittable_list *list);
bool			hittable_list_hit(const t_hittable *self, const t_ray *r,
					t_interval ray_t, t_hit_record *rec);

#endif