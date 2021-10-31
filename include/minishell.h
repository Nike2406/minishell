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
# include <sys/types.h>
# include <sys/errno.h>

# define TOKEN_PIPE						1 // |
# define TOKEN_OR						2 // ||
# define TOKEN_REDIRECT_OUTPUT			3 // >
# define TOKEN_REDIRECT_OUTPUT_APPEND	4 // >>
# define TOKEN_REDIRECT_INPUT			5 // <
# define TOKEN_HEREDOC					6 // <<
# define TOKEN_AND						7 // &&
# define WILDCARD_ASTERISK				8 // *

# define PWD_ERR						1
# define PWD_ERR_OVERWELMING			2

# define CD_ERR							1
# define CD_NO_FILE						2
# define CD_CHDIR						3
# define CD_CWD							4

# define EXPORT_NOT_VALID				1

# define UNSET_NOT_VALID				1

typedef struct s_envp
{
	 char			*key;
	 char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_prog
{
	int				argc;
	char			**argv;
	int				is_argv;
	int				token;
	char			*output_file;
	int				fd_output_file;
	char			*input_file;
	int				fd_input_file;
	char			*heredoc;
	int				fd[2];
	struct s_prog	*head;
	struct s_prog	*next;
}	t_prog;

typedef struct s_shell
{
	char	*input; // считанная строка
	int		child_exit_status; // для $?
	int		fd0_source; // хранить 0-ой фд
	int		fd1_source; // хранить 1-ой фд
	int		fd2_source; // хранить 2-ой фд
	t_prog	*apps;
	t_envp	*environment;
	int		argc;		// junk;
	char	**argv;		// junk;
}			t_shell;

typedef struct s_asterisk
{
	DIR				*dir;
	struct dirent	*cmp;
	int				k;
	int				j;
	int				argc;
}					t_asterisk;

typedef struct s_temp
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
}			t_temp;


//void	sighandler(int sig);
void	add_application(t_shell *minishell);
int		single_quote(t_shell *minishell, int *i);
int		double_quote(t_shell *minishell, int *i);
char	*dollar(t_shell *minishell, int *i);
int		space_cut_begin(t_shell *minishell);
char	**expand_argv(t_shell *minishell, int *i);
char	*split_into_arguments(t_shell *minishell, int *i);
int		tokens_handler(t_shell *minishell, int *i);
int		wildcards_handler(t_shell *minishell, int *i);
void	minishell_executor(t_shell *minishell);
void	garbage_collector(t_shell *minishell);
int		syntax_error(t_shell *minishell, const char *token, int len);
int		standard_error(t_shell *minishell, char *arg_name);
int		executing_error(t_shell *minishell);

void	get_environment(char **env, t_shell *minishell);
int		get_pwd(t_shell *minishell, char **str);
int		get_echo(char **args);
int		echo_check_flag(char *str);
void	write_echo(char **args, int i, int n);
int		get_cd(t_shell *minishell, char **str);
int		get_env(t_shell *minishell, char **str);
char	*find_pwd(t_shell *minishell, char *str);
void	change_old_new_pwd(t_shell *minishell, char *str, char *key);
int		get_export(t_shell *minishell, char **str);
int		sort_export(t_envp **tmp_env);
int		check_export(char **str, t_envp	*env);
int		check_export_dup(t_envp *env, char **arr);
t_envp	*fullfill_env(t_envp *env);
void	ft_lst_swap_01(t_envp **swap);
void	ft_lst_swap_02(t_envp **swap);
void	ft_lst_swap_03(t_envp **swap);
int		get_unset(t_shell *minishell, char **str);
void	check_unset_params(char **str, t_envp *env);
void	unset_del_elem(t_envp *tmp_exp, char *str, int f);
int		get_exit(t_shell *minishell, char **str);
int		get_exec(t_shell *minishell, char **str);
char	*ft_getenv_value(t_envp *lst, char *key);

void	cntrl_c(int sig);

void	ft_lstadd_back_minishell(t_envp **lst, t_envp *new);
void	ft_lstclear_minishell(t_envp **lst);
t_envp	*ft_lstlast_minishell(t_envp *lst);
t_envp	*ft_lstnew_minishell(char *key, char *value);
int		ft_lstsize(t_envp *lst);
t_envp	*ft_lstfirst_minishell(t_envp *lst);
t_envp	*ft_lstdelone_minishell(t_envp *lst);

int		ft_error_pwd(int i);
int		ft_error_cd(int i);
int		ft_error_cd_no_file(int i, char *str);
int		ft_error_export(int i, char *str);
int		ft_error_unset(int i, char *str);

void	check_list(t_envp *list);
char	**get_arr_env(t_envp *env);

void	base_signal(void);
void	input_eof(void);

void	check_shlvl(t_shell *minishell);

#endif
