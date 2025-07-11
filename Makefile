NAME = miniRT
CFLAGS = -Wall -Werror -Wextra -g
SRCS = minirt_src/main.c minirt_src/utils.c minirt_src/vec3.c minirt_src/random.c minirt_src/sphere.c minirt_src/hittable.c minirt_src/vec3_ops4.c minirt_src/material.c minirt_src/hittable_list.c minirt_src/color.c minirt_src/interval.c minirt_src/ray.c minirt_src/vec3_utils.c minirt_src/vec3_ops.c minirt_src/vec3_ops2.c minirt_src/vec3_ops3.c
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
	gcc $(CFLAGS) -o $(NAME) $(OBJS) -Iminirt_src -I$(PRINTF_DIR) -L$(PRINTF_DIR) -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -lftprintf -lft -lmlx -lXext -lX11 -lm

%.o: minirt_src/%.c
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
