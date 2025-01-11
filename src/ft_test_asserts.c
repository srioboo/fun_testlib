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
		printf("\033[0;32m[OK]: \033[0;37m orig %d and new %d are equals \n\n", orig, new);
	}
	else
		printf("\033[0;31m[KO]: \033[0;37m orig %d and new %d are NOT equals \n\n", orig, new);
}
