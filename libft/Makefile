NAME = libft.a

SRC = ft_strncmp.c ft_calloc.c ft_isascii.c ft_memchr.c ft_strchr.c ft_strlcpy.c ft_toupper.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strlen.c ft_substr.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memset.c ft_strjoin.c ft_strrchr.c ft_tolower.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memmove.c ft_strlcat.c ft_memcmp.c ft_strcmp.c ft_split.c ft_strnstr.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_itoa.c

OBJS = $(SRC:.c=.o)

AR = ar rcs

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean