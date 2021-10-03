#include "minishell.h"

void	input_eof(void)
{
	printf("\b\bexit\n");
	exit(0);
}

int lolo(int i)
{
	return i;
}

int	main(int argc, char **argv, char **env)
{
    char	*input;
	char	*termtype;
	(void)argc;
	(void)argv;
	(void)env;

	if (!isatty(STDIN_FILENO))
	{
		write(2, "Not a terminal\n", 15);
		return (1);
	}
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(NULL, termtype) != 1)
	{
		ft_putstr_fd("Can not find terminal or termcap base. ", 2);
		ft_putendl_fd("Please, choose one and define the \"TERM\" variable", 2);
		return (1);
	}
	// int	col = tgetnum("co"); // пример использования tgetnum. "со" возвращает кол-во колонок/полей
	// int	li = tgetnum("li"); // возвращает кол-во линий
	// int	flag_overstrike = tgetflag("os"); // если 0, при вызове символа то что было на той же позиции стирается, не перегружается, иначе нет
	// int	flag_home = tgetflag("hz"); // если 0, терминал может напечатать тильду, иначе нет
	// signal(SIGINT, sighandler);
    while (1)
    {
        input = readline("minishell$ ");
		write(1, "write was here\n", 15);
		tputs(tgoto(tgetstr("ch", NULL), 0, 3), 1, lolo);
		tputs(tgoto(tgetstr("ch", NULL), 0, 15 - 3), 1, lolo);
		//printf("Columns = %s\n", clean_screen);
        if (!input)
            input_eof();
        add_history(input);
		//rl_on_new_line();
		//rl_replace_line(input, 2);
		//rl_clear_history();

        free(input);
    }
}
