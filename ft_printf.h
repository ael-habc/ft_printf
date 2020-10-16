#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

typedef struct	s_syntax
{
	char	flag;
	int		width;
	char	point;
	int		precesion;
	char	length;
	char	type;
}				t_syntax;

int			ft_printf(const char *s, ...);

#endif