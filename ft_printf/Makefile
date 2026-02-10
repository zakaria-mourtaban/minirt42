NAME = libftprintf.a

CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME); 

SRCS = ft_printf.c ft_putchar.c ft_puthex.c ft_putint.c ft_putnbru.c ft_putptr.c ft_putstr.c ft_putfloat.c

OBJS = $(SRCS:.c=.o)

# BONUS_SRCS = ft_lstmap.c ft_lstnew.c ft_lstlast.c ft_lstsize.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstadd_back.c ft_lstadd_front.c

# BONUS_OBJS = $(BONUS_SRCS:.c=.o);

ALL_OBJS= $(OBJS) # $(BONUS_OBJS) 

$(NAME): $(OBJS)
	ar src $(NAME) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
# bonus: $(OBJS) $(BONUS_OBJS)
# 	$(AR) -r $(NAME) $?
# WASM build
WASM_NAME = libftprintf_wasm.a
WASM_OBJS = $(SRCS:.c=.wasm.o)

wasm: $(WASM_NAME)

$(WASM_NAME): $(WASM_OBJS)
	emar rcs $(WASM_NAME) $(WASM_OBJS)

%.wasm.o: %.c
	emcc -Wall -Wextra -O3 -c $< -o $@

clean:
	rm -f $(OBJS:.c=.o) $(BONUS_OBJS:.c=.o) $(WASM_OBJS)
fclean: clean
	rm -f $(NAME) $(WASM_NAME)
re: fclean all

.PHONY: all clean fclean re bonus wasm
