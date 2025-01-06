/* ************************************************************************** */
/*                                                                            */
/*   ft_test_asserts.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	fun_assert_int(int orig, int new)
{
	if (orig == new)
	{
		printf("--- orig %d and new %d are equals \n", orig, new);
	}
	else
		printf("--- orig %d and new %d are NON equals \n", orig, new);
}
