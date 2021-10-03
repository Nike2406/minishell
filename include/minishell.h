#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h> // execve
# include <signal.h> // signal
# include <term.h> // tgetent
# include <termios.h> // tcgetattr, tcsetattr
# include <dirent.h> // opendir, readdir, closedir
# include <sys/errno.h> // нужен ли?

typedef struct s_prog
{
	char	argc;
	char	**argv;
	struct s_prog	*head; // не уверен, что нужен
	struct s_prog	*next;
}	t_prog;

typedef struct s_token
{
	char	argc;
	char	*argv;
	struct	s_token	*head; // не уверен, что нужен
	struct	s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*input; // считанная строка
	char	**envp;	// env
	int		child_exit_status; // для $?
	int		fd0_source; // хранить 0-ой фд
	int		fd1_source; // хранить 1-ой фд
	int		fd2_source; // хранить 2-ой фд
	t_prog	*apps; // список с запускаемыми программами
	t_token	*tokens; // список с токенами

// 		junk
	int		argc;
	char	**argv;
}			t_shell;
//void	sighandler(int sig);
char	*single_quote(t_shell *minishell, int *i);
char	*double_quote(t_shell *minishell, int *i);
char	*dollar(t_shell *minishell, int *i);
char	*space_cut_begin(t_shell *minishell);
char	*space_cut(t_shell *minishell, int *i);
void	minishell_executor(t_shell *minishell);
void	garbage_collector(t_shell *minishell);
#endif