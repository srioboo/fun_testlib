/* ************************************************************************** */
/*                                                                            */
/*   ft_test_asserts.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"

void	fun_assert_int(int orig, int new)
{
	if (orig == new)
	{
		printf("\033[0;32m[OK]: \033[0;37m orig %d and new %d equals \n\n",
			orig, new);
	}
	else
		printf("\033[0;31m[KO]: \033[0;37m orig %d and new %d NOT equals \n\n",
			orig, new);
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
