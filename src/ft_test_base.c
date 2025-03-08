/* ************************************************************************** */
/*                                                                            */
/*   ft_test_base.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

void fun_group_start(const char *method_message)
{
	printf(COLOR_RESET "\n" COLOR_RESET);
	printf(COLOR_BLUE_BKG "=======================");
	printf(COLOR_RESET "\n" COLOR_RESET);
	printf(COLOR_BLUE_BKG "==== %s ====", method_message);
	printf(COLOR_RESET "\n" COLOR_RESET);
	printf(COLOR_BLUE_BKG "=======================" COLOR_RESET);
	printf(COLOR_RESET "\n" COLOR_RESET);
}

void	fun_start(const char *method_message)
{
	printf("\n" COLOR_BLUE "==== START %s ====" COLOR_RESET "\n", method_message);
}

void	fun_end(const char *method_message)
{
	printf("\n" COLOR_BLUE "==== END %s ====" COLOR_RESET "\n\n", method_message);
}

void	fun_test_header(int num)
{
	printf("\n" COLOR_YELLOW "=== Test %d:" COLOR_RESET "\n", num);
}

void	fun_test_header_label(int num, char *str)
{
	printf("\n" COLOR_YELLOW "=== Test %d: (%s)" COLOR_RESET "\n", num, str);
}
