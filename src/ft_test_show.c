/* ************************************************************************** */
/*                                                                            */
/*   ft_test_show.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/testlib.h"

void	fun_show_data(char **test)
{
	while (*test)
	{
		printf("--- '%s' \n", *test);
		test++;
	}
}

void	fun_show_orig_new(int (*forig)(const char *),
			int (*fnew)(const char *), const char *test)
{
	printf("--- orig: %d\n", forig(test));
	printf("---  new: %d\n", fnew(test));
}
