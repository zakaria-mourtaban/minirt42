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
clean:
	rm -f $(OBJS:.c=.o) $(BONUS_OBJS:.c=.o)
fclean: clean
	rm -f $(NAME) 
re: fclean all

.PHONY: all clean fclean re bonus
