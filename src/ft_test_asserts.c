/* ************************************************************************** */
/*                                                                            */
/*   ft_test_asserts.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

int	fun_assert_int(int orig, int new)
{
	int	result;

	if (orig == new)
		result = 1;
	else
		result = 0;
	if (result)
		printf("%s[OK]: %s orig %d and new %d equals \n\n",
			fun_color_ok(), fun_color(COLOR_WHITE), orig, new);
	else
		printf("%s[KO]: %s orig %d and new %d NOT equals \n\n",
			fun_color_ko(), fun_color(COLOR_WHITE), orig, new);
	ft_context_increment_wrapper(result);
	return (result);
}

int	fun_assert_int_fun(int (*f_ori)(const char *str, ...),
		int (*f_new)(const char *str, ...), const char *str, ...)
{
	va_list	args;
	int		value;
	int		result;

	va_start(args, str);
	value = va_arg(args, int);
	result = fun_assert_int(f_ori(str, value), f_new(str, value));
	va_end(args);
	return (result);
}
