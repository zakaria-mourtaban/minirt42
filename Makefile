NAME = miniRT
CFLAGS = -Wall -Werror -Wextra -g
SRCS = source/main.c source/camera_init.c source/utils.c source/vec3.c source/random.c source/sphere.c source/hittable.c source/vec3_ops4.c source/material.c source/hittable_list.c source/color.c source/interval.c source/ray.c source/vec3_utils.c source/vec3_ops.c source/vec3_ops2.c source/vec3_ops3.c source/vec3_print.c source/plane.c source/cylinder.c source/cylinder_quadratic.c source/cylinder_caps.c source/sphere_quadratic.c source/validation/validate_file.c source/parsing/parse_ambient.c source/parsing/parse_camera.c source/parsing/parse_cylinder.c source/parsing/parse_light.c source/parsing/parse_file.c source/parsing/parse_plane.c source/parsing/parse_sphere.c source/validation/validation_utils.c source/validation/validation_utils2.c source/validation/validate_elements.c source/validation/validate_elements2.c source/key_hooks.c source/handle_render.c
OBJS = $(SRCS:%.c=%.o)
PRINTF_DIR = ./ft_printf
LIBFT_DIR = ./libft
MINILIBX_DIR = ./minilibx

# Library files
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MINILIBX_LIB = $(MINILIBX_DIR)/libmlx.a

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_LIB) $(LIBFT_LIB) $(MINILIBX_LIB)
	gcc $(CFLAGS) -o $(NAME) $(OBJS) -Isource -I$(PRINTF_DIR) -L$(PRINTF_DIR) -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -lftprintf -lft -lmlx -lXext -lX11 -lm

%.o: source/%.c
	gcc $(CFLAGS) -c $< -o $@

$(PRINTF_LIB):
	@make -C $(PRINTF_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MINILIBX_LIB):
	@make -C $(MINILIBX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
