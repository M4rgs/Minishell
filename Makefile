NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(HOME)/readline/include #-fsanitize=address -g3

LIBS = -L$(HOME)/readline/lib -lreadline -lncurses

SRC = minishell.c \
	  parsing/tokenizer/tokenizer.c \
	  parsing/tokenizer/syntax_err.c \
	  parsing/tokenizer/tokenizer_utils.c \
	  parsing/signals/signals.c \
	  parsing/quotes/quoted_unquoted.c \
	  parsing/quotes/quoted_utils.c \
	  parsing/heredoc/heredoc.c \
	  parsing/expanding/expanding.c \
	  parsing/expanding/wildcards.c \
	  parsing/expanding/wildcards_utils.c \
	  parsing/expanding/expanding_utils.c \
	  parsing/heredoc/heredoc_utils.c \
	  parsing/heredoc/heredoc_utils2.c \
	  execution/execute/execute.c \
	  execution/execute/check_builtin.c \
	  execution/execute/check_builtin_utils.c \
	  execution/execute/execute_utils.c \
	  execution/redirections/redirections.c \
	  execution/redirections/redirections_utils.c \
	  execution/pipes/pipes.c \
	  execution/pipes/pipes_utils.c \
	  builtins/builtin_pwd/builtin_pwd.c \
	  builtins/builtin_echo/builtin_echo.c \
	  builtins/builtin_export/builtin_export.c \
	  builtins/builtin_export/export_only.c \
	  builtins/builtin_export/builtin_export_utils.c \
	  builtins/builtin_unset/builtin_unset.c \
	  builtins/builtin_exit/builtin_exit.c \
	  builtins/builtin_exit/builtin_exit_utils.c \
	  builtins/builtin_cd/builtin_cd.c \
	  builtins/builtin_env/builtin_env.c \
	  help_fun/utils.c \
	  help_fun/utils2.c \
	  help_fun/utils3.c \
	  help_fun/utils4.c \
	  help_fun/utils5.c \
	  help_fun/utils6.c \
	  help_fun/utils7.c \
	  help_fun/ft_malloc.c \
	  help_fun/ft_split.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c include/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
