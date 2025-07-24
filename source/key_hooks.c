#include "includes/minirt.h"
#include <stdlib.h>

int exit_program(t_scene *scene) {
  hittable_list_free(scene->world);
  free(scene->camera);
  if (scene->win)
    mlx_destroy_window(scene->mlx, scene->win);
  free(scene->mlx);
  exit(0);
}

int key_press_hook(int keycode, t_scene *scene) {
  if (keycode == KEY_ESC)
    exit_program(scene);
  if (keycode == KEY_R && scene->state == INTERACTIVE) {
    ft_printf("\n'R' key pressed. Starting high-quality render...\n");
    scene->state = RENDERING;
  }
  if (keycode >= 0 && keycode < 256)
    scene->keys_pressed[keycode] = true;
  return (0);
}

int key_release_hook(int keycode, t_scene *scene) {
  if (keycode >= 0 && keycode < 256)
    scene->keys_pressed[keycode] = false;
  return (0);
} 