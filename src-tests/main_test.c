/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main_test.c                                                              */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv)
{
	if (!argc)
		printf("%d", argc);
	if (!argv)
		printf("%s", argv[0]);
	fun_group_start("GROUP 1");
	test_ft_dummy(1);
}
