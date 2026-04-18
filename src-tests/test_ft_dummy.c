/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   test_ft_dummy.c                                                        */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	test_ft_dummy(int active)
{
	if (active == 0)
		return (0);
	fun_test_start("test_ft_dummy");
	fun_assert_int(1, 1);
	fun_assert_int(2, 2);
	fun_test_end();
	return (0);
}
