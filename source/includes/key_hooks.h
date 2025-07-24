#ifndef KEY_HOOKS_H
#define KEY_HOOKS_H

#include "minirt.h"

int exit_program(t_scene *scene);
int key_press_hook(int keycode, t_scene *scene);
int key_release_hook(int keycode, t_scene *scene);

#endif 