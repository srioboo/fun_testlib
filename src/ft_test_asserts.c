/* ************************************************************************** */
/*                                                                            */
/*   ft_test_asserts.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

void	fun_assert_int(int orig, int new)
{
	if (orig == new)
	{
		printf("%s[OK]: %s orig %d and new %d equals \n\n",
			fun_color_green(), fun_color_white(), orig, new);
	}
	else
		printf("%s[KO]: %s orig %d and new %d NOT equals \n\n",
			fun_color_red(), fun_color_white(), orig, new);
}

void	fun_assert_int_fun(int (*f_ori)(const char *str, ...),
			int (*f_new)(const char *str, ...), const char *str, ...)
{
	va_list	args;
	int		value;

	va_start(args, str);
	value = va_arg(args, int);
	fun_assert_int(f_ori(str, value), f_new(str, value));
	va_end(args);
}
