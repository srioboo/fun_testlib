/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   test_ft_dummy.c                                                        */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	test_ft_dummy(void)
{
	char	*method_name;
	int		result;

	method_name = (char *)malloc(strlen("test_ft_dummy") * sizeof(char *));
	if (!method_name)
		return (0);
	method_name = "test_ft_dummy";
	result = 0;
	fun_start(method_name);
	fun_test_header(1);
	// add here the functions to test
	fun_end(method_name);
	return (0);
}
