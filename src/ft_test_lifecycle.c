/* ************************************************************************** */
/*                                                                            */
/*   ft_test_lifecycle.c                                :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "funtestlib.h"

static char	*g_current_test = NULL;

void	fun_test_start(const char *name)
{
	if (g_current_test)
		free(g_current_test);
	g_current_test = malloc(strlen(name) + 1);
	if (!g_current_test)
		return ;
	strcpy(g_current_test, name);
	fun_start(name);
	fun_test_header_label(1, (char *)name);
}

void	fun_test_end(void)
{
	fun_end(g_current_test);
	if (g_current_test)
	{
		free(g_current_test);
		g_current_test = NULL;
	}
}
