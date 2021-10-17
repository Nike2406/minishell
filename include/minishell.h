#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h> // execve close read write
# include <signal.h> // signal
# include <term.h> // tgetent
# include <termios.h> // tcgetattr, tcsetattr
# include <dirent.h> // opendir, readdir, closedir
# include <sys/errno.h>

# define TOKEN_PIPE 1 // |
# define TOKEN_OR 2 // ||
# define TOKEN_REDIRECT_OUTPUT 3 // >
# define TOKEN_REDIRECT_OUTPUT_APPEND 4 // >>
# define TOKEN_REDIRECT_INPUT 5 // <
# define TOKEN_HEREDOC 6 // <<
# define TOKEN_AND 7 // &&
# define WILDCARD_ASTERISK 8 // *

typedef struct s_prog
{
	char			argc;
	char			**argv;
	int				is_argv;
	int				token;
	char			*output_file;
	int				fd_output_file;
	char			*input_file;
	int				fd_input_file;
	struct s_prog	*head;
	struct s_prog	*next;
}	t_prog;

typedef struct s_shell
{
	char	*input; // считанная строка
	char	**envp;	// env
	int		child_exit_status; // для $?
	int		fd0_source; // хранить 0-ой фд
	int		fd1_source; // хранить 1-ой фд
	int		fd2_source; // хранить 2-ой фд
	t_prog	*apps; // список с запускаемыми программами

// 		junk
	int		argc;
	char	**argv;
}			t_shell;
//void	sighandler(int sig);
void	add_application(t_shell *minishell);
char	*single_quote(t_shell *minishell, int *i);
char	*double_quote(t_shell *minishell, int *i);
char	*dollar(t_shell *minishell, int *i);
char	*space_cut_begin(t_shell *minishell);
char	**expand_argv(t_shell *minishell, int *i);
char	*split_into_arguments(t_shell *minishell, int *i);
int		tokens_handler(t_shell *minishell, int *i);
int		wildcards_handler(t_shell *minishell, int *i);
void	minishell_executor(t_shell *minishell);
void	garbage_collector(t_shell *minishell);
int		syntax_error(t_shell *minishell, const char symbol);
int		standard_error(t_shell *minishell, char *arg_name);
#endif