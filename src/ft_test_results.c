/* ************************************************************************** */
/*                                                                            */
/*   ft_test_results.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

static t_test_context	g_context = {0};

static void	ft_context_increment(int result)
{
	g_context.total++;
	if (result == 1)
		g_context.passed++;
	else
		g_context.failed++;
}

int	fun_tests_get_exit_code(void)
{
	if (g_context.failed == 0)
		return (0);
	return (1);
}

void	fun_tests_summary(void)
{
	printf("\n%s=================%s\n",
		fun_color(COLOR_BLUE), fun_color_reset());
	printf("%s=== Test Results ===%s\n",
		fun_color(COLOR_BLUE), fun_color_reset());
	printf("%s=================%s\n\n",
		fun_color(COLOR_BLUE), fun_color_reset());
	printf("Total asserts: %d\n", g_context.total);
	printf("%s✓ Passed: %d%s\n",
		fun_color_ok(), g_context.passed, fun_color_reset());
	printf("%s✗ Failed: %d%s\n",
		fun_color_ko(), g_context.failed, fun_color_reset());
	printf("\n");
}

void	fun_tests_reset(void)
{
	g_context.total = 0;
	g_context.passed = 0;
	g_context.failed = 0;
}

void	ft_context_increment_wrapper(int result)
{
	ft_context_increment(result);
}
