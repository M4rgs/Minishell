NAME = minishell

READLINE = readline

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -fsanitize=address

SRC = minishell.c parsing/tokenizer.c execution/execute.c

OBJ = $(SRC:.c=.o)


all: $(READLINE)  $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -o $@ $^  ${LIBFT} -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline -lncurses

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/
	@rm -rf readline-8.2 readline-8.2.tar.gz

re: fclean all

git:
	git add .
	git commit -m "Minishell"
	git push


.PHONY: all clean fclean re
