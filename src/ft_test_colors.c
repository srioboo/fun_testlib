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
		printf("\x1b[3%d%s \t \x1b[0m \x1b[4%d%s\x1b[0m\n", icolor, "mCOLOR", icolor, "mBACKGROUND");
		icolor++;
	}
}

char	*fun_color(char *color)
{
	return (color);
}

char	*fun_color_red(void)
{
	return (COLOR_RED);
}

char	*fun_color_green(void)
{
	return (COLOR_GREEN);
}

char	*fun_color_white(void)
{
	return (COLOR_WHITE);
}

char	*fun_color_reset(void)
{
	return (COLOR_RESET);
}
