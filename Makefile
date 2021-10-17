NAME   :=	minishell
SRC    :=	minishell.c signal_handler.c quotes_handler.c \
			dollar_handler.c split_handler.c executor.c \
			garbage_collector.c tokens_handler.c errors_handler.c \
			app_handler.c wildcards_handler.c signals.c exit.c \
			unset.c export_utils.c utils.c export.c cd.c echo.c \
			errors.c pwd.c lst_functions.c env.c

OBJ    :=	$(SRC:.c=.o)
HDR    :=	minishell.h
CC     :=	gcc
CFLAGS :=	-Wall -Wextra -Werror -MMD
VPATH  :=	src include

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) -C libft
			$(CC) $(CFLAGS) -Llibft -lft -lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1/lib/ -ltermcap $(OBJ) -o $(NAME)

bonus:

%.o: %.c
			$(CC) $(CFLAGS) -Iinclude -Ilibft -I/Users/${USER}/.brew/Cellar/readline/8.1/include -c $< -o $@

include		$(wildcard *.d)

readline:
			brew install readline

readline_uninstall:
			brew uninstall readline		

clean:
			rm -rf *.o *.d
			$(MAKE) clean -C libft

fclean:		clean
			rm -rf $(NAME)
			$(MAKE) fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re bonus readline readline_uninstall
