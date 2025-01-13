/* ************************************************************************** */
/*                                                                            */
/*   ft_test_show.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "testlib.h"

void	fun_show_data(char **message)
{
	while (*message)
	{
		printf("--- '%s' \n", *message);
		message++;
	}
}

void	fun_show_orig_new(int (*forig)(const char *),
			int (*fnew)(const char *), const char *message)
{
	printf("--- orig: %d\n", forig(message));
	printf("---  new: %d\n", fnew(message));
}
