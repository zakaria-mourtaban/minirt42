NAME = miniRT
CFLAGS = -Wall -Werror -Wextra -g
SRCS = minirt_src/main.c minirt_src/random.c minirt_src/sphere.c minirt_src/hittable.c
OBJS = $(SRCS:%.c=%.o)

# Paths to ft_printf, libft, and MinilibX directories
PRINTF_DIR = ./ft_printf
LIBFT_DIR = ./libft
MINILIBX_DIR = ./minilibx

# Library files
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MINILIBX_LIB = $(MINILIBX_DIR)/libmlx.a

# Targets
all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_LIB) $(LIBFT_LIB) $(MINILIBX_LIB) $(PRINTF_DIR)/*.c $(LIBFT_DIR)/*.c $(MINILIBX_DIR)/*.c
	gcc $(CFLAGS) -o $(NAME) $(OBJS) -Iminirt_src -L$(PRINTF_DIR) -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -lftprintf -lft -lmlx -lXext -lX11 -lm

%.o: minirt_src/%.c minirt_src/solong.h
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
