/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:00 by zmourtab          #+#    #+#             */
/*   Updated: 2025/07/08 01:40:00 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/hittable_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include "includes/interval.h"

bool	hittable_list_hit(const t_hittable *self, const t_ray *r,
			t_interval ray_t, t_hit_record *rec)
{
	t_hittable_list	*list;
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	int				i;

	list = (t_hittable_list *)self;
	hit_anything = false;
	closest_so_far = ray_t.max;
	i = 0;
	while (i < list->size)
	{
		if (list->objects[i]->hit(list->objects[i], r, interval_new(ray_t.min,
						closest_so_far), &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
		i++;
	}
	return (hit_anything);
}

t_hittable_list	*hittable_list_new(int capacity)
{
	t_hittable_list	*list;

	list = (t_hittable_list *)malloc(sizeof(t_hittable_list));
	if (!list)
		return (NULL);
	list->objects = (t_hittable **)malloc(sizeof(t_hittable *) * capacity);
	if (!list->objects)
	{
		free(list);
		return (NULL);
	}
	list->size = 0;
	list->capacity = capacity;
	list->hittable.hit = hittable_list_hit;
	return (list);
}

void	hittable_list_add(t_hittable_list *list, t_hittable *object)
{
	if (list->size < list->capacity)
		list->objects[list->size++] = object;
}

void	hittable_list_clear(t_hittable_list *list)
{
	int	i;

	i = 0;
	while (i < list->size)
		free(list->objects[i++]);
	list->size = 0;
}

void	hittable_list_free(t_hittable_list *list)
{
	hittable_list_clear(list);
	free(list->objects);
	free(list);
}
