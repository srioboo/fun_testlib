/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   test_ft_dummy.c                                                        */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	test_ft_dummy(int active)
{
	char	*method_name;
	int		result;

	method_name = fun_method_name("test_ft_dummy");
	result = 0;
	if (active != 0)
	{
		fun_start(method_name);
		fun_test_header(1);
		// add here the functions to test
		fun_assert_int(1, 1);
		fun_assert_int(1, 2);
		fun_end(method_name);
	}
	method_name = fun_free_str(method_name);
	return (result);
}
