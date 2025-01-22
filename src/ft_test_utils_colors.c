/* ************************************************************************** */
/*                                                                            */
/*   ft_test_asserts.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"

char	*fun_red(void)
{
	char	*color;

	color = "\033[0;31m";
	return (color);
}

char	*fun_green(void)
{
	char	*color;

	color = "\033[0;32m";
	return (color);
}

char	*fun_white(void)
{
	char	*color;

	color = "\033[0;37m";
	return (color);
}