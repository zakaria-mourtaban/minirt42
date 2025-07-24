#ifndef HANDLE_RENDER_H
#define HANDLE_RENDER_H

#include "minirt.h"

t_color render_pixel(t_camera *cam, int i, int j, t_scene *scene);
void render_frame(t_scene *scene);
int render_loop(void *param);

#endif 