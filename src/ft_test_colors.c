/* ************************************************************************** */
/*                                                                            */
/*   ft_test_asserts.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

void	fun_color_show(void)
{
	int	icolor;

	icolor = 0;
	while (icolor <= 7)
	{
		printf("\x1b[3%d%s \t \x1b[0m \x1b[4%d%s\x1b[0m\n",
			icolor, "mCOLOR", icolor, "mBACKGROUND");
		icolor++;
	}
}

char	*fun_color(char *color)
{
	return (color);
}

char	*fun_color_ko(void)
{
	return (fun_color(COLOR_RED));
}

char	*fun_color_ok(void)
{
	return (fun_color(COLOR_GREEN));
}

char	*fun_color_reset(void)
{
	return (fun_color(COLOR_RESET));
}
