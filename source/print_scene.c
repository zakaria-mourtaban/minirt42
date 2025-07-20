#include "includes/minirt.h"

void print_scene(const t_scene *scene)
{
	if (scene->camera)
	{
		printf("Camera:\n");
		printf("  lookfrom: (%.2f, %.2f, %.2f)\n", scene->camera->lookfrom.e[0], scene->camera->lookfrom.e[1], scene->camera->lookfrom.e[2]);
		printf("  lookat:   (%.2f, %.2f, %.2f)\n", scene->camera->lookat.e[0], scene->camera->lookat.e[1], scene->camera->lookat.e[2]);
		printf("  vfov: %.2f\n", scene->camera->vfov);
	}
	printf("Ambient:\n");
	printf("  ratio: %.2f\n", scene->ambient_ratio);
	printf("  color: (%.2f, %.2f, %.2f)\n", scene->ambient_color.e[0], scene->ambient_color.e[1], scene->ambient_color.e[2]);
	printf("Light:\n");
	printf("  position: (%.2f, %.2f, %.2f)\n", scene->light.position.e[0], scene->light.position.e[1], scene->light.position.e[2]);
	printf("  brightness: %.2f\n", scene->light.brightness);
	if (scene->world)
		printf("World: %d objects\n", scene->world->size);
	else
		printf("World: (null)\n");
} 