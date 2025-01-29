/* ************************************************************************** */
/*                                                                            */
/*   ft_test_base.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

void	fun_start(const char *method_message)
{
	printf("\n==== TEST: %s ====\n", method_message);
}

void	fun_end(const char *method_message)
{
	printf("\n==== OK: %s ====\n", method_message);
}

void	fun_test_header(int num)
{
	printf("\n=== Test %d:\n", num);
}

void	fun_test_header_label(int num, char *str)
{
	printf("\n=== Test %d: (%s)\n", num, str);
}
