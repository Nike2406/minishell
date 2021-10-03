#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <fcntl.h>
#include <string.h>
#include "./libft/libft.h"

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	struct termios term, term_copy;

// 	int i = tcgetattr(0, &term);
// 	printf("c_ospeed %lu, c_ispeed %lu, term.c_iflag %lu, term.c_oflag %lu,\
// 		term.c_cflag %lu, term.c_lflag %lu ret %d\n", term.c_ospeed, term.c_ispeed, term.c_iflag, term.c_oflag, term.c_cflag, term.c_lflag, i);
	
// 	unsigned int cc;
// 	cc = term.c_cc[VEOF];
// 	printf("cc = %d\n", cc);
// 	term_copy = term;
// }

// struct termios {
// 	tcflag_t        c_iflag;        /* input flags */
// 	tcflag_t        c_oflag;        /* output flags */
// 	tcflag_t        c_cflag;        /* control flags */
// 	tcflag_t        c_lflag;        /* local flags */
// 	cc_t            c_cc[NCCS];     /* control chars */
// 	speed_t         c_ispeed;       /* input speed */
// 	speed_t         c_ospeed;       /* output speed */
// };
int	main(void)
{
	char	*s1;
	char	*s2;

	printf("%d\n", ft_strncmp(s1, s2, 10));
}