#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h> // signal
# include <term.h> // tgetent
# include <termios.h> // tcgetattr, tcsetattr

// Prochell
// Start
#include <sys/types.h>
#include <dirent.h>

# define PWD_ERR				1
# define PWD_ERR_OVERWELMING	2
# define CD_ERR					1
# define CD_NO_FILE				2
// End

typedef struct s_envp
{
	 char			*key;
	 char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;


typedef struct s_shell
{
	char	*input; // считанная строка
	char	**envp;	// env
	int		child_exit_status; // для #?

// 		junk
	int		argc;
	char	**argv;
	// Prochell
	// Start
	t_envp	*environment;
	// End
}			t_shell;
//void	sighandler(int sig);
char	*single_quote(char *input, int *i);
char	*double_quote(t_shell *minishell, int *i);
char	*dollar(t_shell *minishell, int *i);

// Prochell
// Start
void	get_envp(char **env, t_shell *minishell);
int		get_pwd(t_shell *minishell, char **str);
int		get_echo(char **args);
int		echo_check_flag(char *str);
int		get_cd(t_shell *minishell, char **str);

void	ft_lstadd_back_minishell(t_envp **lst, t_envp *new);
void	ft_lstclear_minishell(t_envp **lst);
t_envp	*ft_lstlast_minishell(t_envp *lst);
t_envp	*ft_lstnew_minishell(char *key, char *value);
int		ft_lstsize_ps(t_envp *lst);

int		ft_error_pwd(int i);
int		ft_error_cd(int i);
// End

#endif
